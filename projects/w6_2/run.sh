#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR"

REPS="${REPS:-5}"

# Start every run from a clean build and results tree.
rm -rf results build

RESULTS_DIR="results"
SYSTEM_DIR="$RESULTS_DIR/0_system_info"
BUILD_DIR="$RESULTS_DIR/1_build"
SELF_TEST_DIR="$RESULTS_DIR/2_self_test"
HOTSPOT_DIR="$RESULTS_DIR/3_hotspot_analysis"
SMOKE_DIR="$RESULTS_DIR/4_smoke_test"
FULL_DIR="$RESULTS_DIR/5_full_sweep"

mkdir -p "$SYSTEM_DIR" "$BUILD_DIR" "$SELF_TEST_DIR" "$HOTSPOT_DIR" "$SMOKE_DIR" "$FULL_DIR"

RUN_LOG="$ROOT_DIR/run.log"
: > "$RUN_LOG"
printf '$ ./run.sh\n' >> "$RUN_LOG"

run_logged() {
    local step_log="$1"
    shift

    {
        printf '$'
        printf ' %q' "$@"
        printf '\n'
    } | tee -a "$step_log" "$RUN_LOG"

    {
        "$@"
    } 2>&1 | tee -a "$step_log" >/dev/null
}

run_logged_shell() {
    local step_log="$1"
    shift

    printf '$ %s\n' "$1" | tee -a "$step_log" "$RUN_LOG"

    {
        bash -c "$1"
    } 2>&1 | tee -a "$step_log" >/dev/null
}

# 0_system_info: collect CPU, cache, permission, and PMU event information first.
run_logged_shell "$SYSTEM_DIR/lscpu.log" "lscpu | grep -E 'Model name|NUMA|L1d|L2|L3'"
run_logged "$SYSTEM_DIR/perf_event_paranoid.log" cat /proc/sys/kernel/perf_event_paranoid
run_logged_shell "$SYSTEM_DIR/perf_list.log" "perf list | grep -Ei 'L1-dcache|LLC-load|dTLB-load|l2_rqsts'"
run_logged "$SYSTEM_DIR/perf_list_cache_misses.log" perf list --details cache-misses

# 1_build: compile the benchmark into build/spmv_bench.
mkdir -p build
run_logged "$BUILD_DIR/build.log" g++ -O3 -g -fno-omit-frame-pointer -std=c++17 -Wall -Wextra -Wpedantic \
    src/SpMV_Guided_Benchmark.cpp -o build/spmv_bench

# 2_self_test: run the benchmark's built-in correctness test.
run_logged "$SELF_TEST_DIR/self_test.log" build/spmv_bench --selftest

# 3_hotspot_analysis: profile the permuted layout before the sweeps.
run_logged "$HOTSPOT_DIR/perf_record.log" perf record -g -e cycles:u -o "$HOTSPOT_DIR/profile.data" -- \
    build/spmv_bench --pattern permuted --rows 1048576 --nnz-per-row 8 --iters 60
run_logged_shell "$HOTSPOT_DIR/perf_report.log" "perf report -i '$HOTSPOT_DIR/profile.data' --stdio"
run_logged_shell "$HOTSPOT_DIR/perf_annotate.log" "perf annotate -i '$HOTSPOT_DIR/profile.data' --stdio"

# 4_smoke_test: run one small case before starting the full sweep.
if find "$SMOKE_DIR" -mindepth 1 -print -quit | grep -q .; then
    printf 'Smoke-test results already exist in %s; skipping.\n' "$SMOKE_DIR" | tee -a "$SMOKE_DIR/run_experiment.log" "$RUN_LOG"
else
    run_logged "$SMOKE_DIR/run_experiment.log" python3 scripts/run_SpMV_experiments.py --smoke --reps 1 --out "$SMOKE_DIR"
    run_logged "$SMOKE_DIR/plot.log" python3 scripts/plot_SpMV_results.py "$SMOKE_DIR/summary.csv"
fi

# 5_full_sweep: run the complete experiment set from the clean results tree.
run_logged "$FULL_DIR/run_experiment.log" python3 scripts/run_SpMV_experiments.py --reps "$REPS" --out "$FULL_DIR"
run_logged "$FULL_DIR/plot.log" python3 scripts/plot_SpMV_results.py "$FULL_DIR/summary.csv"

# Record source-file checksums as the final workflow step.
run_logged_shell "$FULL_DIR/sha256sum.log" "sha256sum src/* > SHA256SUMS.txt"

