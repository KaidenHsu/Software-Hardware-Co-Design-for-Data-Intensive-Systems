"""Run RTL tests, DRAM replays, and intensity analysis for the Week 9 SpMV lab."""

import json
import shutil
import subprocess
import sys


def run_verilator(out):
    """Build and execute the four-row RTL smoke test with assertions."""
    v = shutil.which('verilator')
    if not v:
        raise SystemExit('Verilator is unavailable; generate sources now and run on server1')

    # Compile with timing and assertions enabled before executing the testbench.
    src = out / 'sources' / 'week9_spmv_axis.sv'
    tb = out / 'sources' / 'tb_week9_spmv_axis.sv'
    obj = out / 'build'
    obj.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([v,
            '--binary',
            '--timing',
            '--assert',
            '-j',
            '2',
            '--top-module',
            'tb_spmv_axis',
            '--Mdir',
            str(obj),
            str(src),
            str(tb)],
        check=True)
    subprocess.run([str(obj / 'Vtb_spmv_axis')], check=True)


def run_full_verilator(out):
    """Build and execute the file-driven RTL test for every output row."""

    # The testbench reads memory images relative to inputs/.

    v = shutil.which('verilator')
    if not v:
        raise SystemExit('Verilator not installed here; run this command on server1')

    # Match the hardware parameters to this workload manifest.
    meta = json.loads((out / 'w9_manifest.json').read_text())
    cmd = [v,
        '--binary',
        '--timing',
        '--assert',
        '-j',
        '2',
        '--top-module',
        'tb_spmv_file',
        '-GN_ROWS=' + str(meta['rows']),
        '-GTILE=' + str(meta['tile']),
        '-GCMD_COUNT=' + str(meta['command_count']),
        '--Mdir',
        str(out / 'build'),
        str(out / 'sources' / 'week9_spmv_axis.sv'),
        str(out / 'sources' / 'tb_week9_file.sv')]
    subprocess.run(cmd, check=True, cwd=out)
    subprocess.run([str(out / 'build' / 'Vtb_spmv_file')], check=True, cwd=out / 'inputs')


def run_ramulator(out, trace):
    """Replay a generated synthetic trace using the course Python environment."""
    path = out / 'traces' / ('tiled_dma_16B.ldst' if trace == 'tiled' else trace)
    if not path.exists():
        raise SystemExit(f'Trace missing: {path}')

    # Reuse this interpreter so the course Ramulator bindings remain available.
    subprocess.run(
        [sys.executable, str(out / 'sources' / 'week9_ramulator_ddr3.py'),
         str(path), '--report-dir', str(out / 'reports' / 'dram_stats')],
        check=True,
    )


def run_dram_hierarchy(out):
    """Replay equal-count sequential and strided DRAM microbenchmarks."""
    paths = [
        out / 'traces' / 'w9_dram_sequential_16B.ldst',
        out / 'traces' / 'w9_dram_strided_16B.ldst',
    ]
    if not all((x.exists() for x in paths)):
        raise SystemExit('Generate traces first with --make (in this expanded version)')

    # Keep both experiments under the same installed controller configuration.
    for t in paths:
        run_ramulator(out, t.name)
    print('W9_DRAM_HIERARCHY_REPLAY_COMPLETED=YES (inspect controller metrics and drain)')


def run_roofline(out, sustained_gb_s):
    """Write integer operations per DMA byte without assuming bandwidth."""

    # Count one integer multiply and add per MAC; omit host preprocessing.

    p = out / 'w9_manifest.json'
    if not p.exists():
        raise SystemExit('Generate inputs first with --make')
    m = json.loads(p.read_text())
    ops = 2 * m['macs']
    bytes_ = m['command_bytes'] + m['y_output_bytes']
    oi = ops / bytes_
    d = {
        'kernel': 'CSR SpMV, signed integer multiply + add',
        'math_intops': ops,
        'accelerator_dma_input_output_bytes_minimum': bytes_,
        'arithmetic_intensity_intops_per_dma_byte': oi,
        'ideal_core_cycles_excluding_stalls_and_external_data_movement': m['optimistic_core_cycles'],
        'assumed_clock_mhz': 100,
        'ideal_core_intops_per_second_at_assumed_clock': ops / (m['optimistic_core_cycles'] / 100000000.0),
        'caveats': ['Not floating-point FLOP/s.',
            'DMA minimum excludes software bucketing, PS memory touches, DDR3 command overhead, and cache maintenance.',
            'This is a model intensity, not a measured platform Roofline; compare with separately measured sustained bandwidth and actual FPGA execution.']
    }

    # A bandwidth estimate is included only when explicitly supplied by the user.
    if sustained_gb_s is not None:
        if sustained_gb_s <= 0:
            raise SystemExit('Sustained GB/s must be positive')
        d['user_supplied_sustained_bandwidth_GB_per_s'] = sustained_gb_s
        d['bandwidth_limited_intops_per_second_assuming_achievable_BW'] = oi * sustained_gb_s * 1000000000.0
        d['disclaimer'] = 'User-supplied bandwidth is unverified; NOT measured by this command.'

    report_dir = out / 'reports'
    report_dir.mkdir(parents=True, exist_ok=True)
    path = report_dir / 'w9_roofline_intensity_proxy.json'
    path.write_text(json.dumps(d, indent=2) + '\n')
    print('W9_INTENSITY_PROXY=PASS', json.dumps(d, indent=2))
