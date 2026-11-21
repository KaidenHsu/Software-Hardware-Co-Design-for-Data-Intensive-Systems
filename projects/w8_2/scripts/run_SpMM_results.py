#!/usr/bin/env python3
"""Self-contained SpMM profiling. Runs separate CORE and LEVELS kernel-only PMU passes.
Each pass starts in a fresh process with a correctness-checked warm-up.
Unmeasurable or multiplexed events remain N/A
"""

import argparse, csv, hashlib, os, random, statistics, subprocess, sys
from pathlib import Path

# Parse the benchmark output into key=value fields for correctness and metrics.
def fields(text):
    result={}
    for line in text.splitlines():
        for word in line.split():
            if '=' in word:
                k,v=word.split('=',1)
                result[k]=v
    return result

# Accept numeric values except missing entries, N/A, and NaN.
def valid(v):
    try: return bool(v and v!='N/A' and float(v)==float(v))
    except (ValueError, TypeError): return False

# Configure repetitions, an optional smoke workload, and the output directory.
def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--reps',type=int,default=5)
    parser.add_argument('--smoke',action='store_true')
    parser.add_argument('--out',type=Path,default=None,
                        help='Output directory; defaults to 4_smoke_test with --smoke, otherwise 5_full_sweep.')
    a=parser.parse_args()
    if a.reps<1 or a.reps>20: parser.error('reps must be 1..20')

    # Locate the executable and outputs relative to the project, regardless of cwd.
    root=Path(__file__).resolve().parent.parent
    executable=root/'build'/'spmm_gnn'
    if not executable.is_file() or not os.access(executable,os.X_OK):
        sys.exit('Compile the benchmark first (see README).')

    # Reuse the requested output directory so repeated runs can refresh results.
    default_out=Path('results/4_smoke_test' if a.smoke else 'results/5_full_sweep')
    selected_out=a.out if a.out is not None else default_out
    out=(selected_out if selected_out.is_absolute() else root/selected_out).resolve()
    csv_dir=out/'csv'
    csv_dir.mkdir(parents=True,exist_ok=True)
    (out/'logs').mkdir(parents=True,exist_ok=True)

    # Pin this process and its benchmark children to one allowed logical CPU.
    affinity=sorted(os.sched_getaffinity(0)) if hasattr(os,'sched_getaffinity') else []
    cpu=affinity[0] if affinity else None
    if cpu is not None: os.sched_setaffinity(0,{cpu}) # 0: current process, {cpu}: new allowed CPU set

    # Collect host information without aborting if an optional command fails.
    def safe(cmd):
        try:
            r=subprocess.run(cmd, text=True, capture_output=True,timeout=30)
            return r.stdout.strip() if r.returncode==0 else 'N/A: '+r.stderr.strip()
        except (OSError, subprocess.TimeoutExpired) as exc:return 'N/A: '+str(exc)

    # Record host details, measurement scope, and source hashes for reproducibility.
    prov=['kernel=SpMM', f'cpu_affinity={cpu}', f'reps={a.reps}',
          'Two SEPARATE process executions per rep/layout: core counters then cache/TLB counters.',
          'Counts cover user-space timed loop only. Cache events are not DRAM traffic.',
          'Only retain counter counts when running_fraction >= 0.99.',
          safe(['uname','-a']),safe(['lscpu']), safe(['g++','--version']).splitlines()[0]]
    for file in ['SpMM_GNN_Aggregation_Benchmark.cpp', 'di_common.hpp','di_kernel_pmu.hpp']:
        prov.append(file+' SHA256='+hashlib.sha256((root/'src'/file).read_bytes()).hexdigest())
    (out/'provenance.txt').write_text('\n'.join(prov)+'\n')

    # Each case is (rows, features, iterations).
    cases=[(r,f,it) for (r,it) in [(8192,100),(32768,60),(131072,25),(262144,12)] for f in (8,32)]
    if a.smoke: cases=[(8192,0,2)] if 'SpMM'=='SpMV' else [(8192,8,2)]

    # Define one raw CSV row per repetition/layout, combining both PMU passes.
    cols=['rows','features','iters','pattern','rep','CORRECT','checksum','timed_kernel_s',
          'ms_per_iter','ns_per_edge_feature','feature_table_MiB', 'PMU_STATUS','cycles','instructions',
          'cache_misses','ipc','core_running_fraction','LEVEL_STATUS',
          'l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses',
          'levels_running_fraction','levels_unavailable_events']
    records=[]


    # =====================================================================
    #              START EXPERIMENT NESTED LOOP
    # =====================================================================
    # 1. For each workload size
    for rows,features,iters in cases:
        # Shuffle layout/repetition order with a fixed seed to reduce ordering bias.
        schedule=[(rep,layout) for rep in range(1,a.reps+1) for layout in ('local','permuted')]
        random.Random(rows*971+features*107).shuffle(schedule)

        # 2. For each repetition and layout
        for rep,pattern in schedule:
            base_args = ['--rows',str(rows),'--nnz-per-row','8','--features',str(features),'--iters',str(iters)]
            output={}

            for mode,modeflag in [
                # 3.1 Run the benchmark with core counters.
                ('core','--pmu'),
                # 3.2 Run the benchmark with cache/TLB counters.
                ('levels','--pmu-levels'),
            ]:
                cmd=[str(executable),modeflag,'--pattern',pattern]+base_args
                try:r=subprocess.run(cmd,capture_output=True,text=True,timeout=900)
                except subprocess.TimeoutExpired:
                    sys.exit('TIMEOUT 900 seconds: '+str(cmd))

                # Preserve the command and all output before checking for failures.
                log=out/'logs'/f'R{rows}_F{features}_{pattern}_rep{rep}_{mode}.log'
                log.write_text('$ '+' '.join(cmd)+'\n\n'+r.stdout+r.stderr)
                if r.returncode:
                    sys.exit('FAILED '+str(log)+' (exit '+str(r.returncode)+')')

                # Require a correct numerical result and the requested PMU mode.
                data=fields(r.stdout)
                if data.get('CORRECT')!='PASS':sys.exit('Correctness FAIL: '+str(log))
                if data.get('PMU_MODE')!=mode:sys.exit('PMU mode missing or wrong: '+str(log))
                # stores the parsed output from each PMU mode in output
                output[mode]=data

            # 3.3 Combine both outputs into one measurement record.

            # Require both passes to agree before merging their metrics.
            core,lev=output['core'],output['levels']
            if core['checksum']!=lev['checksum']:
                sys.exit('Core and levels passes disagree in correctness checksum')
            obj={key:core.get(key,'') for key in cols}
            obj.update(rows=rows,features=features,iters=iters,pattern=pattern,rep=rep)
            obj['LEVEL_STATUS']=lev.get('PMU_STATUS','UNAVAILABLE')
            obj['core_running_fraction']=core.get('running_fraction','N/A')
            obj['levels_running_fraction']=lev.get('running_fraction','N/A')
            obj['levels_unavailable_events']=lev.get('PMU_UNAVAILABLE_EVENTS','')
            for key in ('l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses'):
                obj[key]=lev.get(key,'N/A')

            # Discard counts when counters ran for less than 99% of the measured time.
            # Multiplexed raw counts must never be presented as complete event counts.
            if not valid(obj['core_running_fraction']) or float(obj['core_running_fraction']) < 0.99:
                for key in ('cycles','instructions','cache_misses','ipc'):obj[key]='N/A'
            if not valid(obj['levels_running_fraction']) or float(obj['levels_running_fraction']) < 0.99:
                for key in ('l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses'):
                    obj[key]='N/A'

            # Retain the validated record and print progress for long-running sweeps.
            records.append(obj)
            print(f'R={rows} F={features} {pattern} rep={rep} core={obj["PMU_STATUS"]} levels={obj["LEVEL_STATUS"]}',flush=True)
    # =====================================================================
    #              END EXPERIMENT NESTED LOOP
    # =====================================================================



    # =====================================================================
    #              START raw.csv
    # =====================================================================
    # Save individual measurements so the summary can be independently inspected.
    with (csv_dir/'raw.csv').open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=cols)
        w.writeheader()
        w.writerows(records)
    # =====================================================================
    #              END raw.csv
    # =====================================================================



    # =====================================================================
    #              START summary.csv
    # =====================================================================
    # Defines the columns for summary.csv
    summary_fields=['rows','features','pattern','reps','median_ms_per_iter','median_normalized_ns',
                    'stddev_normalized_ns','median_ipc','median_cycles','median_cache_misses',
                    'median_l1d_load_misses','median_l2_demand_rd_misses',
                    'median_llc_load_misses','median_dtlb_load_misses',
                    'core_pmu_ok_count','levels_pmu_ok_count','all_correct']

    # Summarize repetitions using medians, with standard deviation for normalized time.
    with (csv_dir/'summary.csv').open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=summary_fields)
        w.writeheader()

        for rows,features,_ in cases:
            for pattern in ('local','permuted'):
                group=[v for v in records if int(v['rows'])==rows and int(v['features'])==features
                       and v['pattern']==pattern]

                # Ignore unavailable samples; report N/A if no usable samples remain.
                def median(key):
                    v=[float(x[key]) for x in group if valid(x.get(key))]
                    return round(statistics.median(v),6) if v else 'N/A'

                # Track timing variability, usable PMU passes, and numerical correctness.
                norm=[float(x['ns_per_edge_feature']) for x in group]
                stats={'rows':rows,
                      'features':features,
                      'pattern':pattern,
                      'reps':len(group),
                      'median_ms_per_iter':median('ms_per_iter'),
                      'median_normalized_ns':median('ns_per_edge_feature'),
                      'stddev_normalized_ns':round(statistics.stdev(norm),6) if len(norm)>1 else 0,
                      'median_ipc':median('ipc'), 'median_cycles':median('cycles'),
                      'median_cache_misses':median('cache_misses'),
                      'core_pmu_ok_count':sum(x['PMU_STATUS'] in ('OK','PARTIAL') for x in group),
                      'levels_pmu_ok_count':sum(x['LEVEL_STATUS'] in ('OK','PARTIAL') for x in group),
                      'all_correct':all(x['CORRECT']=='PASS' for x in group)}
                for key in ('l1d_load_misses','l2_demand_rd_misses','llc_load_misses','dtlb_load_misses'):
                    stats['median_'+key]=median(key)
                w.writerow(stats)
    # =====================================================================
    #              END summary.csv
    # =====================================================================

    # Emit the completion marker only after both CSV files have been written.
    print('RUN_COMPLETE=PASS folder='+str(out))

# Run the experiment only when invoked directly.
if __name__=='__main__':main()
