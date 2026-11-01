#!/usr/bin/env python3
"""Run the benchmark self-test and tee its output to a log file."""

import subprocess
import sys
from pathlib import Path


def main():
    # Resolve paths from the project root so the script can be run from any
    # working directory.
    root = Path(__file__).resolve().parent.parent
    executable = root / 'build' / 'spmm_gnn'
    log_dir = root / 'results' / '2_self_test'
    log_path = log_dir / 'Self_Test.log'

    if not executable.is_file() or not executable.stat().st_mode & 0o111:
        sys.exit('Build the benchmark first (see README).')

    log_dir.mkdir(parents=True, exist_ok=True)
    command = [str(executable), '--selftest']

    # Stream combined stdout/stderr to the terminal and the log simultaneously.
    with log_path.open('w') as log:
        log.write('$ ./build/spmm_gnn --selftest\n\n')
        process = subprocess.Popen(
            command,
            cwd=root,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
        )
        assert process.stdout is not None
        for line in process.stdout:
            sys.stdout.write(line)
            sys.stdout.flush()
            log.write(line)
            log.flush()
        return_code = process.wait()
        log.write(f'\n[exit_code={return_code}]\n')

    print(f'SELF_TEST_LOG={log_path}')
    return return_code


if __name__ == '__main__':
    raise SystemExit(main())
