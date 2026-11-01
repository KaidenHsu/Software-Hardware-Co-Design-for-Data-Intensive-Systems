#!/usr/bin/env bash

# Reproduce the project's generated results in workflow order.
set -euo pipefail

# Make the script independent of the directory from which it is launched.
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

run_cmd() {
    printf '$'
    printf ' %q' "$@"
    printf '\n'
    if ! "$@" >/dev/null 2>&1; then
        printf 'Command failed:' >&2
        printf ' %q' "$@" >&2
        printf '\n' >&2
        return 1
    fi
}

# Remove generated build and result artifacts so this run starts clean.
run_cmd rm -rf build/ results/

# Create the complete output layout before any workflow step runs.
run_cmd mkdir -p \
    build \
    results/0_system_info \
    results/1_build \
    results/2_self_test \
    results/3_hotspot_analysis \
    results/4_smoke_test/csv \
    results/4_smoke_test/logs \
    results/5_full_sweep/csv \
    results/5_full_sweep/logs \
    results/5_full_sweep/plots \
    results/6_targeted_pmu_test

# Collect processor, kernel, and PMU information.
run_cmd python3 scripts/system_info.py

# Compile the benchmark and validate both layouts and PMU modes.
run_cmd python3 scripts/verify_benchmark.py

# Run the small independent CSR correctness test.
run_cmd python3 scripts/self_test.py

# Record and summarize a sampled hotspot profile.
run_cmd python3 scripts/hotspot_analysis.py

# Run the repeated two-mode experiment sweep.
run_cmd python3 scripts/run_SpMM_results.py --reps 5 --out results/5_full_sweep

# Generate SVG plots from the completed sweep summary.
run_cmd python3 scripts/plot_SpMM_results.py results/5_full_sweep/csv/summary.csv

# Run the four targeted PMU measurements for both layouts and counter modes.
run_cmd python3 scripts/targeted_pmu_test.py
