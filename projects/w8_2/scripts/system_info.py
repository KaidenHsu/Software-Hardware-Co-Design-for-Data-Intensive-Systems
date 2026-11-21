#!/usr/bin/env python3
"""Collect host and PMU information into separate system-information logs."""

import subprocess
from pathlib import Path


def main():
    root = Path(__file__).resolve().parent.parent
    log_dir = root / 'results' / '0_system_info'
    log_dir.mkdir(parents=True, exist_ok=True)

    commands = [
        ('lscpu.log', "lscpu | grep -E 'Model name|NUMA|L1d|L2|L3'"),
        ('perf_event_paranoid.log', 'cat /proc/sys/kernel/perf_event_paranoid'),
        ('perf_list.log', "perf list | grep -Ei 'L1-dcache|LLC-load|dTLB-load|l2_rqsts'"),
        ('perf_details_cache_misses.log', 'perf list --details cache-misses'),
    ]
    for filename, command in commands:
        log_path = log_dir / filename
        result = subprocess.run(
            command,
            cwd=root,
            shell=True,
            capture_output=True,
            check=False,
            text=True,
        )
        with log_path.open('w') as log:
            log.write(f'$ {command}\n\n')
            log.write(result.stdout)
            if result.stderr:
                log.write('\n[stderr]\n')
                log.write(result.stderr)
            log.write(f'\n[exit_code={result.returncode}]\n')

    print(f'SYSTEM_INFO_LOGS={log_dir}')


if __name__ == '__main__':
    main()
