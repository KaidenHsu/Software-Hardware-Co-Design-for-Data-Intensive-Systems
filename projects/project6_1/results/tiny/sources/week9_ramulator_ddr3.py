"""Replay a synthetic trace with the patched course Ramulator installation.

Run with /home/asinha/tools/week8/venv/bin/python on server1. The 16-bit
DDR3 channel is a proxy, not an emulation of the PS AXI/DMA datapath.
"""

import argparse
import json
import pathlib

import ramulator


# Validate the trace before passing it to the simulator frontend.
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('trace', type=pathlib.Path)
parser.add_argument('--report-dir', type=pathlib.Path, default=None,
                    help='Report directory (default: beside the trace)')
args = parser.parse_args()
trace = args.trace.expanduser().resolve()
if not trace.is_file():
    raise SystemExit('Trace not found')

lines = trace.read_text().splitlines()
if not lines or any(
    (
        len(p := ln.split()) != 2
        or p[0] not in ('LD', 'ST')
        or int(p[1], 0) % 16 != 0
    )
    for ln in lines
):
    raise SystemExit('Trace format/alignment invalid')

# Keep the DRAM model, scheduling policy, and mapper explicit for reporting.
frontend = ramulator.frontend.LoadStoreTrace(clock_ratio=1, path=str(trace))
dram = ramulator.dram.DDR3(
    org_preset='DDR3_4Gb_x16',
    timing_preset='DDR3_1066F',
    rank=1,
    channel_width=16,
)
ctrl = ramulator.controller.GenericDDR(
    dram=dram,
    scheduler=ramulator.scheduler.FRFCFS(),
    refresh_manager=ramulator.refresh_manager.AllBank(),
    row_policy=ramulator.row_policy.Open(),
    addr_mapper=ramulator.addr_mapper.RoBaRaCoCh(),
)
mem = ramulator.memory_system.GenericDRAM(
    clock_ratio=1,
    controllers=[ctrl],
    channel_mapper=ramulator.channel_mapper.CacheLineInterleave(),
)

# Preserve genuine simulator counters before finalizing the simulation.
sim = ramulator.Simulation(frontend, mem)
sim.run()
yaml = sim.stats_yaml
stats = sim.stats
sim.finalize()

# Standalone replay keeps its historical default of writing beside the trace.
report_dir = args.report_dir.expanduser().resolve() if args.report_dir else trace.parent
report_dir.mkdir(parents=True, exist_ok=True)
output = report_dir / trace.with_suffix('.ramulator_stats.yaml').name
output.write_text(yaml)

# Accept either supported single-controller statistics representation.
ctrl = (
    stats.get('memory_system', {}).get('controller', {})
    if isinstance(stats, dict)
    else {}
)
if isinstance(ctrl, list):
    if len(ctrl) != 1:
        raise SystemExit('Expected exactly one DDR3 controller for this lab')
    ctrl = ctrl[0]

if not isinstance(ctrl, dict) or any(
    k not in ctrl for k in ('cycles', 'row_hits', 'row_misses', 'row_conflicts')
):
    raise SystemExit(
        'W9_DRAM_STATS_UNAVAILABLE: controller cycles/row-hit/miss/conflict '
        'stats not found; check locally installed Ramulator and inspect YAML'
    )

# Copy exposed counters only; do not infer row behavior from address spacing.
metrics = {
    'source_trace': str(trace),
    'source_requests': len(lines),
    'source_reads': sum(ln.startswith('LD ') for ln in lines),
    'source_writes': sum(ln.startswith('ST ') for ln in lines),
    'controller': 'DDR3_4Gb_x16 / DDR3_1066F / 1 channel / FRFCFS / Open / RoBaRaCoCh',
    'assumed_tCK_ps': 1875,
    'note': (
        'Standalone normalized-injection controller replay; '
        'not PYNQ-Z2 or FPGA end-to-end time.'
    ),
}
for key in (
    'cycles',
    'avg_read_latency',
    'num_read_reqs',
    'num_write_reqs',
    'row_hits',
    'row_misses',
    'row_conflicts',
    'read_queue_len_avg',
    'write_queue_len_avg',
):
    if key in ctrl:
        try:
            metrics[key] = float(ctrl[key])
        except (ValueError, TypeError):
            metrics[key] = str(ctrl[key])

if 'cycles' in metrics:
    metrics['controller_modeled_ms'] = metrics['cycles'] * 1875 / 1e9

h = metrics.get('row_hits')
m = metrics.get('row_misses')
c = metrics.get('row_conflicts')
if h is not None and m is not None and c is not None and (h + m + c) > 0:
    metrics['row_hit_fraction_of_classified_accesses'] = h / (h + m + c)

# Write normalized metrics beside the raw statistics in the report directory.
mpath = report_dir / trace.with_suffix('.ramulator_metrics.json').name
mpath.write_text(json.dumps(metrics, indent=2) + '\n')
print(
    'W9_RAMULATOR_RUN_RETURNED trace=', trace, 'records=', len(lines),
    'tCK_ps=1875 stats=', output, 'metrics=', mpath,
)
print(
    'IMPORTANT: verify accepted/completed/outstanding counts in patched Ramulator stats;'
    ' no end-to-end FPGA speedup claim'
)
