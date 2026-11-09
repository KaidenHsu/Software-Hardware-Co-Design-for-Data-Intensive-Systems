#!/usr/bin/env python3
"""Server1 Week8 CSR SpMV memory payload normalization, DDR4 vs HBM2.

Separate teaching sensitivity experiment. For each gem5 64-byte request, keep
one 64-byte DDR4 request, but generate two adjacent 32-byte HBM2 requests.
Requires existing modified Ramulator2 source with W8_DRAIN_CALLBACK_PATCH_V1.
This is NOT coupled gem5/Ramulator timing or a full HBM-stack speedup test.
The frontend replays one transaction per clock cycle, without gem5 timestamps.

Called by the pipeline with explicit trace directories, never a "latest" lookup.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import sys
import experiment_stages

# --- Model assumptions and source-trace validation ----------------------------
CLK_PS = {'ddr4': 833, 'hbm2': 1000}  # timing preset tCK values; confirm installed source


def require(ok, text):
    """Raise a payload-validation error when the required condition is false."""
    if not ok: raise RuntimeError('W8_PAYLOAD_FAIL: '+text)


def sha(path):
    """Compute a file SHA-256 digest in chunks without loading the whole trace into memory."""
    h=hashlib.sha256()
    with open(path,'rb') as f:
        for chunk in iter(lambda:f.read(1<<20),b''):
            h.update(chunk)
    return h.hexdigest()


# --- Transform aligned 64-byte packets into two 32-byte HBM2 transactions. ---
def prepare(src_dir, out):
    """Validate 64-byte source requests, write paired HBM2 records, and return replay inputs."""
    orig=src_dir/'spmv_roi_postL2.trace'
    info=src_dir/'kernel_trace_manifest.json'
    require(orig.is_file() and info.is_file(),f'missing trace/manifest: {src_dir}')
    m=json.loads(info.read_text())
    require(m.get('trace_sha256') == sha(orig), 'kernel trace hash mismatch')

    # Byte equivalence requires every original request to represent exactly 64 bytes.
    sizes={str(k):int(v) for k,v in m.get('size_histogram_bytes',{}).items()}
    require(sizes=={'64':int(m['output_records'])},
            'need exclusively 64-byte gem5 transactions; actual histogram='+str(sizes))
    require(m['read']+m['write']==m['output_records'],'bad manifest counts')

    out.mkdir(parents=True, exist_ok=True)
    hbm=out/'hbm2_32byte.trace'
    count={'LD':0,'ST':0}; alignment_errors=0
    with orig.open() as fin, hbm.open('w') as fout:
        for n,line in enumerate(fin,1):
            parts=line.strip().split()
            require(len(parts)==2 and parts[0] in ('LD','ST'),f'bad trace line {n}')
            a=int(parts[1],0)
            if a%64: alignment_errors+=1
            require(a>=0 and a%64==0, f'nonaligned 64-byte gem5 packet line {n}: {a:#x}')
            # Retain the operation and split the cache line at its 32-byte midpoint.
            fout.write(f'{parts[0]} 0x{a:x}\n')
            fout.write(f'{parts[0]} 0x{a+32:x}\n')
            count[parts[0]]+=1

    # Check decoded counts against provenance metadata before recording new inputs.
    require(count['LD']==m['read'] and count['ST']==m['write'],
            'request count mismatch with manifest')
    require(sum(count.values())==m['output_records'],'line count mismatch')

    manifest={'gem5_trace_path':str(orig),'gem5_trace_sha256':sha(orig),
              'gem5_request_sizes':sizes,'original_ld':count['LD'],
              'original_st':count['ST'],'ddr4_requests':sum(count.values()),
              'hbm2_requests':2*sum(count.values()),
              'ddr4_payload_bytes':64*sum(count.values()),
              'hbm2_payload_bytes':32*2*sum(count.values()),
              'hbm2_trace_sha256':sha(hbm),
              'remark':'Each aligned original 64B packet split into two 32B HBM pseudochannel transactions. No source modifications.'}
    require(manifest['ddr4_payload_bytes']==manifest['hbm2_payload_bytes'],
            'payload mismatch')
    (out/'input_manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return orig,hbm,m,out

# --- Isolated backend process and callback/statistics accounting --------------
def internal_backend(name,trace,out):
    """Run one memory model in the backend process and write its raw YAML statistics."""
    import ramulator

    # Internal mode owns the simulation; the parent process audits its output.
    frontend=ramulator.frontend.LoadStoreTrace(clock_ratio=1,path=str(trace))
    if name=='ddr4':
        dram=ramulator.dram.DDR4(org_preset='DDR4_8Gb_x8',timing_preset='DDR4_2400R',rank=1)
        controller=ramulator.controller.GenericDDR
    else:
        dram=ramulator.dram.HBM2(org_preset='HBM2_2Gb',timing_preset='HBM2_2000Mbps')
        controller=ramulator.controller.HBM12

    ctrl=controller(dram=dram,scheduler=ramulator.scheduler.FRFCFS(),
                    refresh_manager=ramulator.refresh_manager.AllBank(),
                    row_policy=ramulator.row_policy.Open(),
                    addr_mapper=ramulator.addr_mapper.RoBaRaCoCh())
    mem=ramulator.memory_system.GenericDRAM(clock_ratio=1,controllers=[ctrl],
                    channel_mapper=ramulator.channel_mapper.CacheLineInterleave())

    sim=ramulator.Simulation(frontend,mem)
    sim.run()
    stats=sim.stats_yaml
    sim.finalize()
    (out/f'{name}_stats.yaml').write_text(str(stats),encoding='utf8')


def run_backend(name,trace,out,timeout=3600,log=None):
    """Launch an isolated backend, capture its log, and return parsed drain-completion counts."""
    log=log or out/f'{name}_replay.log'
    call=[sys.executable,str(Path(__file__).resolve()),'--internal-backend',name,
          '--internal-trace',str(trace),'--internal-out',str(out)]
    s=experiment_stages.run(call, log, timeout=timeout)

    # The installed drain patch prints exactly one completion summary per backend.
    matches=re.findall(r'W8_DRAIN_PASS submitted=(\d+) completed=(\d+) '
                       r'outstanding=(\d+) drain_ticks=(\d+)',s)
    require(len(matches)==1,f'{name} missing single valid completion callback; see {log}')
    return tuple(map(int,matches[0]))


def read_stats(path):
    """Load YAML and return the memory-system and sole controller statistics dictionaries."""
    import yaml
    doc=yaml.safe_load(path.read_text())
    c=doc['memory_system']['controller']
    if isinstance(c,list):
        require(len(c)==1,'expected one channel');c=c[0]
    return doc['memory_system'],c


# --- Public CLI orchestration and private subprocess entry point. ---
def main(argv=None):
    # Internal mode runs in a fresh process; public mode transforms and audits traces.
    """Dispatch backend mode or prepare, replay, audit, and summarize byte-equivalent cases."""
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--run',action='store_true')
    p.add_argument('--source-dir',type=Path,action='append',help='Explicit results/<pattern>/trace directory; repeat for both patterns')
    p.add_argument('--out-dir',type=Path,help='Run directory containing per-pattern replay_byte_equiv results')
    log_options = p.add_mutually_exclusive_group()
    log_options.add_argument('--log-file', type=Path, help='Append all backend commands to this stage log')
    log_options.add_argument('--log-dir', type=Path, help='Standalone per-backend command-log directory')
    p.add_argument('--replay-timeout',type=int,default=3600,help='Seconds allowed per backend replay')
    p.add_argument('--ramulator-root',type=Path,default=Path('/home/asinha/tools/week8/ramulator2'),help='Read-only installed Ramulator2 source')
    p.add_argument('--internal-backend',choices=['ddr4','hbm2'])
    p.add_argument('--internal-trace',type=Path)
    p.add_argument('--internal-out',type=Path)
    a=p.parse_args(argv)
    if a.internal_backend:
        require(a.internal_trace and a.internal_out,'invalid internal invocation')
        internal_backend(a.internal_backend,a.internal_trace,a.internal_out)
        return

    # Public mode prepares traces and runs each memory technology in a child process.
    require(a.run,'run with --run')
    require(a.replay_timeout > 0, 'replay timeout must be positive')
    require(a.source_dir and a.out_dir, 'public mode requires --source-dir and --out-dir')
    import yaml  # noqa
    import ramulator  # noqa
    ramroot=a.ramulator_root.expanduser().resolve()
    patched=ramroot/'src/ramulator/frontend/impl/memory_trace/loadstore_trace.cpp'
    require(patched.is_file() and 'W8_DRAIN_CALLBACK_PATCH_V1' in patched.read_text(),
            'Ramulator callback/drain patch absent from installed source')

    all_results={}
    for source in a.source_dir:
        source=source.resolve()
        pattern=source.parent.name
        require(pattern in ('scattered','clustered') and pattern not in all_results,
                'source directories must belong to distinct scattered/clustered cases')
        original,hbm,m,out=prepare(source, a.out_dir/pattern/'replay_byte_equiv')
        entry={'source_directory':str(source),'source_trace_sha256':sha(original),
               'gem5_roi_ticks':m['roi_ticks'],'size_histogram':m['size_histogram_bytes']}

        # DDR4 consumes the original trace; HBM2 consumes the two-record-per-line trace.
        for name,trace in [('ddr4',original),('hbm2',hbm)]:
            print('RUN',pattern,name,'trace',trace,flush=True)
            log=a.log_file if a.log_file else (a.log_dir/f'{pattern}_{name}.log' if a.log_dir else None)
            submitted,completed,outstanding,drain_ticks=run_backend(name,trace,out,a.replay_timeout,log)
            expect=int(m['output_records'])*(2 if name=='hbm2' else 1)
            require((submitted,completed,outstanding)==(expect,expect,0),
                    f'{pattern} {name} callback count mismatch: {(submitted,completed,outstanding)} vs {expect}')

            # Check accepted requests and completed work independently of callbacks.
            ms,c=read_stats(out/f'{name}_stats.yaml')
            r=int(m['read'])*(2 if name=='hbm2' else 1)
            w=int(m['write'])*(2 if name=='hbm2' else 1)
            require(ms['total_num_read_requests']==r and ms['total_num_write_requests']==w,
                    f'{pattern} {name} accepted count mismatch')
            done_r=int(c['num_read_reqs_served'])+int(c.get('num_read_reqs_forwarded',0))
            done_w=int(c['num_write_reqs_served'])+int(c.get('num_write_reqs_coalesced',0))
            require(done_r==r and done_w==w,
                    f'{pattern} {name} served count mismatch: {done_r}/{r} and {done_w}/{w}')

            # Convert controller cycles with the assumed model clock period, in ps.
            cycles=int(c['cycles'])
            entry[name]={'requests':expect,'read':r,'write':w,'callbacks_completed':completed,
                         'outstanding':outstanding,'drain_ticks':drain_ticks,
                         'controller_cycles':cycles,
                         'assumed_preset_tCK_ps':CLK_PS[name],
                         'modeled_controller_time_ms':cycles*CLK_PS[name]/1e9,
                         'avg_read_latency_cycles':float(c['avg_read_latency']),
                         'row_hits':int(c['row_hits']), 'row_misses':int(c['row_misses']),
                         'row_conflicts':int(c['row_conflicts']),
                         'reported_throughput_MBps':float(c['total_throughput_MBps'])}

            # Cross-check reported bandwidth against the expected logical byte total.
            payload=64 if name=='ddr4' else 32
            effective_bytes=entry[name]['reported_throughput_MBps']*1e6*(cycles*CLK_PS[name]/1e12)
            required_bytes=expect*payload
            relerr=abs(effective_bytes-required_bytes)/required_bytes
            require(relerr<0.03,f'{pattern} {name} reported throughput implies unexpected byte count: {effective_bytes} vs {required_bytes}')
            print(f'W8_PAYLOAD_{pattern.upper()}_{name.upper()}=PASS',flush=True)

        entry['replay_time_ratio_ddr4_to_hbm2']=entry['ddr4']['modeled_controller_time_ms']/entry['hbm2']['modeled_controller_time_ms']
        all_results[pattern]=entry
        (out/'verification.json').write_text(json.dumps(entry,indent=2)+'\n')

    # Combine cases while preserving the experiment's interpretation limits.
    final={'status':'PASS','payload_equivalent_per_original_packet_bytes':64,
           'results':all_results,'limitations':[
             'HBM2 64B gem5 requests represented as 2x32B transactions; DDR4 retains 1x64B',
             'gem5 time and request sizes are not replayed; frontend issues requests at normalized 1-per-cycle',
             'single Ramulator modeled channel; not full DDR4 subsystem or complete HBM stack',
             'two different backends have different channel structures and address mapping',
             'gem5 ROI timestamp-filtered post-L2 stream includes possible non-data or outstanding traffic',
             'no gem5 closed-loop coupling; no physical FPGA or CPU memory speedup claimed']}
    output=a.out_dir/'payload_equivalent_summary.json'
    output.write_text(json.dumps(final,indent=2)+'\n')
    print('W8_PAYLOAD_EQUIVALENT=PASS',flush=True)
    print('W8_OUTPUT='+str(output),flush=True)



# Keep backend failures visible to the caller through a nonzero process exit.
if __name__=='__main__':
    try: main()
    except Exception as exc:
        print(type(exc).__name__+': '+str(exc),file=sys.stderr,flush=True)
        sys.exit(1)
