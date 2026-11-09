#!/usr/bin/env python3
"""Ramulator 2.1 ordered LD/ST replay of a decoded gem5 POST-L2 trace.

Uses the supplied, preinstalled CMU-SAFARI/ramulator2 Python package with the
classroom callback/drain patch. The pipeline audits completion after this script
returns; a standalone invocation only runs the backends and saves their stats.

Both models use one JEDEC channel, one request/cycle FRONTEND attempt, and a
1:1 frontend:memory tick ratio solely for cycle-domain sensitivity analysis.
This is NOT calibrated CPU/DRAM real-time comparison and the frontend ignores
original gem5 request spacing and byte sizes. Never describe cycles as ns.
"""
import argparse
import json
from pathlib import Path


# --- Backend construction: one controller, normalized request injection -------
def execute(dram_name, trace_path, out_dir):
    """Replay one LD/ST trace through the chosen Ramulator model and save its YAML statistics."""
    import ramulator

    # Input records contain operations and addresses; original gem5 timing is absent.
    frontend = ramulator.frontend.LoadStoreTrace(clock_ratio=1, path=str(trace_path))

    # The trace stays the same; this branch selects its controller and DRAM model.
    if dram_name == 'DDR4':
        dram = ramulator.dram.DDR4(org_preset='DDR4_8Gb_x8',
                                   timing_preset='DDR4_2400R', rank=1)
        controller = ramulator.controller.GenericDDR
    elif dram_name == 'HBM2':
        dram = ramulator.dram.HBM2(org_preset='HBM2_2Gb',
                                   timing_preset='HBM2_2000Mbps')
        controller = ramulator.controller.HBM12
    else:
        raise ValueError(dram_name)

    # Connect scheduling, refresh, row policy, and address mapping to one controller.
    ctrl = controller(dram=dram, scheduler=ramulator.scheduler.FRFCFS(),
                      refresh_manager=ramulator.refresh_manager.AllBank(),
                      row_policy=ramulator.row_policy.Open(),
                      addr_mapper=ramulator.addr_mapper.RoBaRaCoCh())
    mem = ramulator.memory_system.GenericDRAM(
        clock_ratio=1, controllers=[ctrl],
        channel_mapper=ramulator.channel_mapper.CacheLineInterleave())

    # This is a standalone replay, with no CPU feeding back memory-response latency.
    sim = ramulator.Simulation(frontend, mem)
    sim.run()
    stats_yaml = sim.stats_yaml
    sim.finalize()

    # Capture statistics before finalization, then persist them for the wrapper audit.
    out_file = out_dir / f'{dram_name.lower()}_stats.yaml'
    out_file.write_text(str(stats_yaml), encoding='utf-8')
    print(f'{dram_name}: stats saved to {out_file}')


# --- Standalone CLI: explicit input trace and output directory ----------------
def main():
    """Validate a text trace, record input metadata, and run the requested memory technologies."""
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('loadstore_trace', type=Path)
    p.add_argument('--out-dir', type=Path, default=Path('w8_ramulator_results'))
    p.add_argument('--technology', choices=['ddr4', 'hbm2'], help='Run one backend (default: both)')
    a = p.parse_args()

    # Validate the exported LD/ST format before starting either model.
    if not a.loadstore_trace.is_file():
        p.error('LD/ST trace does not exist')
    lines = a.loadstore_trace.read_text().splitlines()
    if not lines or any(len(s.split()) != 2 or s.split()[0] not in ('LD','ST') for s in lines):
        p.error('expected nonempty Ramulator2 LoadStoreTrace: LD/ST <physical-address>')

    # Record the input contract: request order survives, timestamps and sizes do not.
    a.out_dir.mkdir(parents=True, exist_ok=True)
    (a.out_dir/'input_manifest.json').write_text(json.dumps({
       'records': len(lines), 'reads': sum(s.startswith('LD ') for s in lines),
       'writes': sum(s.startswith('ST ') for s in lines),
       'timing_preserved': False, 'size_preserved': False,
       'front_mem_clock_ratio': '1:1, normalized; not calibrated for time'},indent=2)+'\n')

    # The pipeline normally requests one model per process for isolated backend state.
    for variant in ((a.technology.upper(),) if a.technology else ('DDR4','HBM2')):
        execute(variant, a.loadstore_trace.resolve(), a.out_dir)


if __name__ == '__main__':
    main()
