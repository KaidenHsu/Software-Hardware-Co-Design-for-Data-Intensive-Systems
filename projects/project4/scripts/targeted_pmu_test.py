#!/usr/bin/env python3
"""Run the four targeted PMU measurements described in the README."""

import subprocess
import sys
from pathlib import Path


def run_logged(command, display_command, log_path, root):
    """Run one PMU measurement and save its command and complete output."""
    result = subprocess.run(
        command,
        cwd=root,
        text=True,
        capture_output=True,
        check=False,
    )

    # Keep the exact command at the top so each log is independently useful.
    log_path.write_text(
        f'$ {display_command}\n\n'
        + result.stdout
        + (f'\n[stderr]\n{result.stderr}' if result.stderr else '')
        + f'\n[exit_code={result.returncode}]\n'
    )

    if result.returncode:
        raise SystemExit(f'Command failed; see {log_path}')


def main():
    root = Path(__file__).resolve().parent.parent
    executable = root / 'build' / 'spmm_gnn'
    output = root / 'results' / '6_targeted_pmu_test'

    if not executable.is_file() or not executable.stat().st_mode & 0o111:
        sys.exit('Build the benchmark first (see README).')

    output.mkdir(parents=True, exist_ok=True)

    # Run each layout once in each PMU mode. The modes are separate processes
    # because the core and cache/TLB counters are not collected simultaneously.
    cases = [
        ('local_pmu.log', '--pmu --pattern local'),
        ('local_pmu_levels.log', '--pmu-levels --pattern local'),
        ('permuted_pmu.log', '--pmu --pattern permuted'),
        ('permuted_pmu_levels.log', '--pmu-levels --pattern permuted'),
    ]
    common = '--rows 131072 --nnz-per-row 8 --features 32 --iters 30'

    for filename, options in cases:
        display_command = f'./build/spmm_gnn {options} {common}'
        command = [str(executable)] + options.split() + common.split()
        run_logged(command, display_command, output / filename, root)

    print(f'TARGETED_PMU_LOGS={output}')


if __name__ == '__main__':
    main()
