#!/usr/bin/env python3
"""Self-contained SpMV profiling. Runs separate CORE and LEVELS kernel-only PMU passes.
Each pass starts in a fresh process with a correctness-checked warm-up.
Unmeasurable or multiplexed events remain N/A; no hardware counters are invented.
"""
import argparse
import csv
import hashlib
import os
import random
import shutil
import statistics
import subprocess
import sys
from pathlib import Path


def fields(text):
    """Parse key=value tokens emitted by the benchmark."""
    result={}

    for line in text.splitlines():
        for word in line.split():
            if '=' in word:
                k,v=word.split('=',1)
                result[k]=v

    return result


def valid(v):
    """Return whether a value is a usable finite numeric counter result."""
    try: return bool(v and v!='N/A' and float(v)==float(v))
    except (ValueError, TypeError): return False


def main():
    """Run repeated core and cache/TLB PMU passes and write CSV summaries."""

    # Parse command-line options.
    parser=argparse.ArgumentParser()
    parser.add_argument('--reps',type=int,default=5)
    parser.add_argument('--smoke',action='store_true')
    parser.add_argument('--out',type=Path,default=Path('results'))
    a=parser.parse_args()
    if a.reps<1 or a.reps>20: parser.error('reps must be 1..20')

    # Resolve all project paths from the repository root, independent of cwd.
    root=Path(__file__).resolve().parent.parent
    executable=root/'build'/'spmv_bench'
    if not executable.is_file() or not os.access(executable,os.X_OK):
        sys.exit('Compile the benchmark first (see README).')

    # Replace the selected output directory so every invocation starts fresh.
    out=(a.out if a.out.is_absolute() else root/a.out).resolve()
    if out.exists(): shutil.rmtree(out)
    (out/'logs').mkdir(parents=True,exist_ok=True)

    # Pin the runner to one permitted logical CPU for more repeatable measurements.
    affinity=sorted(os.sched_getaffinity(0)) if hasattr(os,'sched_getaffinity') else []
    cpu=affinity[0] if affinity else None
    if cpu is not None: os.sched_setaffinity(0,{cpu})

    def safe(cmd):
        """Collect optional system provenance without failing the experiment."""
        try:
            r=subprocess.run(cmd, text=True, capture_output=True,timeout=30)
            return r.stdout.strip() if r.returncode==0 else 'N/A: '+r.stderr.strip()
        except (OSError, subprocess.TimeoutExpired) as exc:return 'N/A: '+str(exc)

    # Record host and source information alongside every result set.
    prov=['kernel=SpMV', f'cpu_affinity={cpu}', f'reps={a.reps}',
          'Two SEPARATE process executions per rep/layout: core counters then cache/TLB counters.',
          'Counts cover user-space timed loop only. Cache events are not DRAM traffic.',
          'Only retain counter counts when running_fraction >= 0.99.',
          safe(['uname','-a']),safe(['lscpu']), safe(['g++','--version']).splitlines()[0]]
    for file in ['src/SpMV_Guided_Benchmark.cpp', 'src/di_common.hpp','src/di_kernel_pmu.hpp']:
        prov.append(file+' SHA256='+hashlib.sha256((root/file).read_bytes()).hexdigest())

    (out/'provenance.txt').write_text('\n'.join(prov)+'\n')

    # Each tuple contains rows, feature count, and timed iterations.
    cases=[(16384,0,400),(65536,0,300),(262144,0,100),(1048576,0,40),(2097152,0,20)]

    if a.smoke: cases=[(8192,0,2)] if 'SpMV'=='SpMV' else [(8192,8,2)]

    cols=['rows','features','iters','pattern','rep','CORRECT','checksum','timed_kernel_s',
          'ms_per_iter','ns_per_nnz','x_MiB', 'PMU_STATUS','cycles','instructions',
          'cache_misses','ipc','core_running_fraction','LEVEL_STATUS',
          'l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses',
          'levels_running_fraction','levels_unavailable_events']

    records=[]

    # Shuffle case order so system drift is not always correlated with matrix size.
    for rows,features,iters in cases:
        schedule=[(rep,layout) for rep in range(1,a.reps+1) for layout in ('local','permuted')]
        random.Random(rows*971+features*107).shuffle(schedule)

        for rep,pattern in schedule:
            base_args = ['--rows',str(rows),'--nnz-per-row','8','--iters',str(iters)]
            output={}

            # Run core and cache/TLB counters in separate processes to avoid counter oversubscription.
            for mode,modeflag in [('core','--pmu'),('levels','--pmu-levels')]:
                cmd=[str(executable),modeflag,'--pattern',pattern]+base_args
                try:r=subprocess.run(cmd,capture_output=True,text=True,timeout=900)
                except subprocess.TimeoutExpired:
                    sys.exit('TIMEOUT 900 seconds: '+str(cmd))

                # Preserve complete stdout/stderr for post-run diagnosis.
                log=out/'logs'/f'R{rows}_F{features}_{pattern}_rep{rep}_{mode}.txt'
                log.write_text(' '.join(cmd)+'\n'+r.stdout+'\n'+r.stderr)
                if r.returncode:
                    sys.exit('FAILED '+str(log)+' (exit '+str(r.returncode)+')')

                data=fields(r.stdout)
                if data.get('CORRECT')!='PASS':sys.exit('Correctness FAIL: '+str(log))
                if data.get('PMU_MODE')!=mode:sys.exit('PMU mode missing or wrong: '+str(log))
                output[mode]=data

            core,lev=output['core'],output['levels']
            if core['checksum']!=lev['checksum']:
                sys.exit('Core and levels passes disagree in correctness checksum')

            # Combine the two passes only after matching their correctness checksums.
            obj={key:core.get(key,'') for key in cols}
            obj.update(rows=rows,features=features,iters=iters,pattern=pattern,rep=rep)
            obj['LEVEL_STATUS']=lev.get('PMU_STATUS','UNAVAILABLE')
            obj['core_running_fraction']=core.get('running_fraction','N/A')
            obj['levels_running_fraction']=lev.get('running_fraction','N/A')
            obj['levels_unavailable_events']=lev.get('PMU_UNAVAILABLE_EVENTS','')
            for key in ('l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses'):
                obj[key]=lev.get(key,'N/A')
            # Multiplexed raw counts must never be presented as complete event counts.
            if not valid(obj['core_running_fraction']) or float(obj['core_running_fraction']) < 0.99:
                for key in ('cycles','instructions','cache_misses','ipc'):obj[key]='N/A'
            if not valid(obj['levels_running_fraction']) or float(obj['levels_running_fraction']) < 0.99:
                for key in ('l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses'):
                    obj[key]='N/A'

            records.append(obj)
            print(f'R={rows} F={features} {pattern} rep={rep} core={obj["PMU_STATUS"]} levels={obj["LEVEL_STATUS"]}',flush=True)

    # Write one row per layout and repetition before calculating medians.
    with (out/'raw.csv').open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=cols);w.writeheader();w.writerows(records)

    summary_fields=['rows','features','pattern','reps','median_ms_per_iter','median_normalized_ns',
                    'stddev_normalized_ns','median_ipc','median_cycles','median_cache_misses',
                    'median_l1d_load_misses','median_l2_demand_rd_misses',
                    'median_llc_load_misses','median_dtlb_load_misses',
                    'core_pmu_ok_count','levels_pmu_ok_count','all_correct']

    # Summarize each matrix size and layout using robust medians.
    with (out/'summary.csv').open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=summary_fields);w.writeheader()

        for rows,features,_ in cases:
            for pattern in ('local','permuted'):
                group=[v for v in records if int(v['rows'])==rows and int(v['features'])==features
                       and v['pattern']==pattern]

                def median(key):
                    v=[float(x[key]) for x in group if valid(x.get(key))]
                    return round(statistics.median(v),6) if v else 'N/A'

                norm=[float(x['ns_per_nnz']) for x in group]
                stats={'rows':rows,'features':features,'pattern':pattern,'reps':len(group),
                      'median_ms_per_iter':median('ms_per_iter'),
                      'median_normalized_ns':median('ns_per_nnz'),
                      'stddev_normalized_ns':round(statistics.stdev(norm),6) if len(norm)>1 else 0,
                      'median_ipc':median('ipc'), 'median_cycles':median('cycles'),
                      'median_cache_misses':median('cache_misses'),
                      'core_pmu_ok_count':sum(x['PMU_STATUS'] in ('OK','PARTIAL') for x in group),
                      'levels_pmu_ok_count':sum(x['LEVEL_STATUS'] in ('OK','PARTIAL') for x in group),
                      'all_correct':all(x['CORRECT']=='PASS' for x in group)}
                for key in ('l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses'):
                    stats['median_'+key]=median(key)

                w.writerow(stats)

    print('RUN_COMPLETE=PASS folder='+str(out))


if __name__=='__main__':
    main()
