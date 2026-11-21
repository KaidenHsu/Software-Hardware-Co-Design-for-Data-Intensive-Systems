"""Prepare simulation inputs and supporting sources for the Week 9 signed-integer SpMV lab."""

import hashlib
import json
import math
import shutil
import struct
from pathlib import Path

from model_workload import gen_case, gen_tiny

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SOURCE_FILES = {
    'week9_spmv_axis.sv': 'rtl/week9_spmv_axis.sv',
    'tb_week9_spmv_axis.sv': 'tb/tb_week9_spmv_axis.sv',
    'tb_week9_file.sv': 'tb/tb_week9_file.sv',
    'week9_ramulator_ddr3.py': 'templates/week9_ramulator_ddr3.py'
}


def digest(p):
    """Return the SHA-256 digest of a file."""
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()


def write_bytes(out, commands, y, m):
    """Write binary streams, memory images, and synthetic DRAM traces."""

    inputs = out / 'inputs'
    traces = out / 'traces'
    inputs.mkdir(parents=True, exist_ok=True)
    traces.mkdir(parents=True, exist_ok=True)

    # These 16-byte requests model a DDR3 boundary, not captured AXI traffic.

    with (inputs / 'dma_commands.bin').open('wb') as f, (inputs / 'cmds.memh').open('w') as h:
        for c in commands:
            f.write(struct.pack('<Q', c))
            h.write(f'{c:016x}\n')

    # Emit the same oracle as packed signed words and hexadecimal memory text.
    with (inputs / 'expected_y.bin').open('wb') as f, (inputs / 'expected.memh').open('w') as h:
        for n in y:
            f.write(struct.pack('<i', n))
            h.write(f'{n & 0xffffffff:08x}\n')

    # Model contiguous command reads and result writes in 16-byte requests.
    data_bytes = 8 * len(commands)
    y_bytes = 4 * len(y)
    with (traces / 'tiled_dma_16B.ldst').open('w') as f:
        for i in range(math.ceil(data_bytes / 16)):
            f.write(f'LD 0x{0x10000000 + 16 * i:x}\n')
        for i in range(math.ceil(y_bytes / 16)):
            f.write(f'ST 0x{0x20000000 + 16 * i:x}\n')

    # Hold request count fixed while changing the synthetic address stride.
    for name, stride in [('w9_dram_sequential_16B.ldst', 16), ('w9_dram_strided_16B.ldst', 8192)]:
        with (traces / name).open('w') as f:
            for i in range(4096):
                f.write(f'LD 0x{0x01000000 + stride * i:x}\n')

    # Attach the trace accounting and modeling boundary to the manifest.
    m.update({
            'dram_microbenchmark_records': 4096,
            'dram_microbenchmark_logical_read_bytes': 65536,
            'dram_microbenchmark_strides_B': {
                'sequential': 16,
                'strided': 8192
            },
            'dram_microbenchmark_caveat': 'Same number of 16B reads and unique addresses, different footprints and bank/row mapping; no CPU cache simulation.',
            'ddr3_proxy_line_bytes': 16,
            'tiled_dma_read_requests_16B': math.ceil(data_bytes / 16),
            'tiled_dma_write_requests_16B': math.ceil(y_bytes / 16),
            'ddr3_proxy_read_bytes_with_padding': 16 * math.ceil(data_bytes / 16),
            'ddr3_proxy_write_bytes_with_padding': 16 * math.ceil(y_bytes / 16),
            'trace_caveat': 'Synthetic contiguous PS DMA reads/writes, NOT measured DDR3 or AXI traffic; independent normalized-load Ramulator replay'
        })


def make(args):
    """Generate a workload and copy simulator sources into its output directory."""

    # Keep generated filenames compatible with the course simulator commands.

    out = Path(args.out).expanduser().resolve()
    out.mkdir(parents=True, exist_ok=True)
    if args.tiny:
        cmds, y = gen_tiny()
        m = {
            'rows': 4,
            'nonzeros_per_row': 'varies',
            'nnz': 6,
            'cols': 5,
            'pattern': 'Week 7 original exact oracle',
            'tile': 8,
            'macs': 6,
            'x_loads': 5,
            'command_count': len(cmds),
            'command_bytes': 8 * len(cmds),
            'y_output_bytes': 16,
            'optimistic_core_cycles': 2 + 3 * 4 + 5 + 2 * 6
        }
    else:
        cmds, y, m = gen_case(args.rows, args.nnz_per_row, args.cols, args.pattern, args.tile)

    inputs = out / 'inputs'
    sources = out / 'sources'
    sources.mkdir(parents=True, exist_ok=True)
    (out / 'reports' / 'dram_stats').mkdir(parents=True, exist_ok=True)

    write_bytes(out, cmds, y, m)
    for name, source in SOURCE_FILES.items():
        shutil.copyfile(PROJECT_ROOT / source, sources / name)

    # Hash generated data so later reports can identify the exact workload.
    m['sha256'] = {
        name: digest(out / name)
        for name in (
            'inputs/dma_commands.bin',
            'inputs/expected_y.bin',
            'traces/tiled_dma_16B.ldst',
        )
    }
    (out / 'w9_manifest.json').write_text(json.dumps(m, indent=2) + '\n')
    assert len((inputs / 'dma_commands.bin').read_bytes()) == 8 * len(cmds)
    assert len((inputs / 'expected_y.bin').read_bytes()) == 4 * len(y)
    print('W9_GENERATE=PASS', json.dumps(m, indent=2))
    print('W9_OUT=', out)
    return out
