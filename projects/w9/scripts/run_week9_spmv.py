#!/usr/bin/env python3
"""Run the Week 9 SpMV lab; use --help to list generation and simulation options.

Execute from any working directory. Lab helpers live in scripts/; hardware and testbenches live in rtl and tb.
Synthetic controller replays and RTL cycles are not physical FPGA measurements.
"""

import argparse
from pathlib import Path

from prep_simulation_files import PROJECT_ROOT, make
from model_workload import gen_case, gen_tiny
from run_experiments import (run_verilator,
    run_full_verilator,
    run_ramulator,
    run_dram_hierarchy,
    run_roofline)


def main():
    """Parse lab options and execute the selected generation or simulator steps."""
    p = argparse.ArgumentParser(description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    # Keep direct CLI runs in the project, even when invoked from elsewhere.
    p.add_argument(
        '--out',
        default=str(PROJECT_ROOT / 'results' / 'medium'),
        help='Workload directory (default: project results/medium)',
    )
    p.add_argument('--selftest', action='store_true')
    p.add_argument('--make', action='store_true')
    p.add_argument('--tiny', action='store_true')
    p.add_argument('--rows', type=int, default=1024)
    p.add_argument('--nnz-per-row', type=int, default=8)
    p.add_argument('--cols', type=int, default=4096)
    p.add_argument('--tile', type=int, default=2048)
    p.add_argument('--pattern', choices=['clustered', 'scattered'], default='scattered')

    # Simulator operations consume a previously generated workload directory.
    p.add_argument('--verilator', action='store_true')
    p.add_argument('--verilator-full', action='store_true')
    p.add_argument('--ramulator', action='store_true')
    p.add_argument('--dram-hierarchy',
        action='store_true',
        help='Run two equal-request-count synthetic bank/row locality microbenchmarks')
    p.add_argument('--roofline',
        action='store_true',
        help='Compute an arithmetic-intensity and DMA-byte proxy (not a measured roofline)')
    p.add_argument('--sustained-gb-s',
        type=float,
        default=None,
        help='Optional user-measured sustained bandwidth; no default or fabricated value')

    # Dispatch only explicitly requested lab operations.
    args = p.parse_args()

    if args.selftest:
        cmds, y = gen_tiny()
        assert y == [6, 6, -1, 15] and len(cmds) == 13
        for pat in ('clustered', 'scattered'):
            for tile in (16, 128, 512, 2048):
                cmd, y, m = gen_case(65, 7, 4096, pat, tile)
                assert len(cmd) == m['command_count'] and m['macs'] == 455
        print('W9_PYTHON_SELFTEST=PASS tiny=[6,6,-1,15], 8 tiling cases verified')

    # Generation precedes simulator dispatch when options are combined.
    if args.make:
        make(args)
    out = Path(args.out).expanduser().resolve()
    if args.verilator:
        run_verilator(out)
    if args.verilator_full:
        run_full_verilator(out)
    if args.ramulator:
        run_ramulator(out, 'tiled')
    if args.dram_hierarchy:
        run_dram_hierarchy(out)
    if args.roofline:
        run_roofline(out, args.sustained_gb_s)
    if not (args.selftest or args.make or args.verilator or args.verilator_full or args.ramulator or args.dram_hierarchy or args.roofline):
        p.print_help()


if __name__ == "__main__":
    main()
