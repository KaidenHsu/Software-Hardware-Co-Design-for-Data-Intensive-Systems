#!/usr/bin/env python3
"""Record and summarize a benchmark hotspot profile with Linux perf."""

import argparse
import subprocess
import sys
from pathlib import Path


def run(command, output_path, cwd):
    # Capture each perf command, including stderr and its exit status, so the
    # profiling workflow can be audited without rerunning it.
    result = subprocess.run(command, cwd=cwd, text=True, capture_output=True, check=False)
    output_path.write_text(
        '$ ' + ' '.join(command) + '\n\n' + result.stdout
        + ('\n[stderr]\n' + result.stderr if result.stderr else '')
        + f'\n[exit_code={result.returncode}]\n'
    )
    if result.returncode:
        raise SystemExit(f'Command failed; see {output_path}')


def main():
    # Allow the profiling workload to be changed without editing the script.
    parser = argparse.ArgumentParser()
    parser.add_argument('--pattern', choices=('local', 'permuted'), default='permuted')
    parser.add_argument('--rows', type=int, default=131072)
    parser.add_argument('--nnz-per-row', type=int, default=8)
    parser.add_argument('--features', type=int, default=32)
    parser.add_argument('--iters', type=int, default=30)
    args = parser.parse_args()

    # Resolve all inputs and outputs from the project root, independent of the
    # directory from which the script is launched.
    root = Path(__file__).resolve().parent.parent
    executable = root / 'build' / 'spmm_gnn'
    system_info = root / 'results' / '0_system_info'
    output = root / 'results' / '3_hotspot_analysis'

    # Profiling requires both the compiled benchmark and system-information
    # logs, which document the PMU events available on the host.
    if not executable.is_file() or not executable.stat().st_mode & 0o111:
        sys.exit('Build the benchmark first (see README).')
    if not system_info.is_dir():
        sys.exit('Run scripts/system_info.py first; system-information logs are missing.')

    # Store all profiling artifacts next to the system-information logs.
    output.mkdir(parents=True, exist_ok=True)

    # Build the benchmark command used as the workload for perf record.
    benchmark = [str(executable), '--pattern', args.pattern,
                 '--rows', str(args.rows), '--nnz-per-row', str(args.nnz_per_row),
                 '--features', str(args.features), '--iters', str(args.iters)]
    profile = output / 'profile.data'
    record = ['perf', 'record', '-g', '-e', 'cycles:u', '-o', str(profile), '--'] + benchmark

    # Record sampled call stacks first, then derive the textual report and
    # source-level annotation from the resulting profile data.
    run(record, output / 'record.log', root) # perf record
    run(['perf', 'report', '-i', str(profile), '--stdio'], output / 'report.log', root) # perf report
    run(['perf', 'annotate', '-i', str(profile), '--stdio'], output / 'annotate.log', root) # perf annotate

    # Preserve the system-information source and workload parameters alongside
    # the profile so the analysis can be reproduced later.
    (output / 'provenance.log').write_text(
        f'system_info={system_info}\n'
        f'pattern={args.pattern} rows={args.rows} nnz_per_row={args.nnz_per_row} '
        f'features={args.features} iters={args.iters}\n'
    )
    print(f'HOTSPOT_ANALYSIS_LOGS={output}')


if __name__ == '__main__':
    main()
