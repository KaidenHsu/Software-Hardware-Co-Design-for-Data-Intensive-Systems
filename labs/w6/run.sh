#!/usr/bin/env bash
set -Eeuo pipefail

# Run from any working directory while keeping all generated files in the
# project. The caller may override root, for example: root=/path/to/w6 ./run.sh.
root="${root:-$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)}"
src="$root/src/CSR_SpMV_benchmark_kernel_PMU.cpp"
log="$root/log"
build="$root/build"
perf_dir="$root/perf"

# Each run starts with fresh human-readable logs and perf recordings.
if [[ "$root" == "/" || -z "$root" ]]; then
    printf 'ERROR: refusing to remove log/perf from an unsafe root: %s\n' "$root" >&2
    exit 1
fi
rm -rf -- "$log" "$perf_dir"

mkdir -p \
    "$log/0_system_info" \
    "$log/1_baseline" \
    "$log/2_perf_stat" \
    "$log/3_pmu_col4" \
    "$log/4_pmu_col16" \
    "$log/5_perf_record" \
    "$log/6_perf_report" \
    "$build" \
    "$perf_dir"

run_logged() {
    local output="$1"
    shift
    {
        printf '$'
        printf ' %q' "$@"
        printf '\n\n'
        "$@"
    } >"$output" 2>&1
}

# Record machine and perf configuration before running the benchmark.
run_logged "$log/0_system_info/perf_path.log" \
    command -v perf
run_logged "$log/0_system_info/system.log" \
    uname -a
run_logged "$log/0_system_info/cpu_info.log" \
    lscpu
run_logged "$log/0_system_info/perf_access.log" \
    cat /proc/sys/kernel/perf_event_paranoid
run_logged "$log/0_system_info/perf_events.log" \
    perf list

# The Makefile owns compilation and incremental rebuilds. This script only
# runs the experiments using the binaries supplied by make.
baseline="$build/spmv_profile"
pmu_col4="$build/spmv_profile_pmu_col4"
pmu_col16="$build/spmv_profile_pmu_col16"
for binary in "$baseline" "$pmu_col4" "$pmu_col16"; do
    if [[ ! -x "$binary" ]]; then
        printf 'ERROR: missing executable %s; run "make" first\n' "$binary" >&2
        exit 1
    fi
done

run_logged "$log/1_baseline/spmv_profile_local.log" \
    "$baseline" --pattern local --rows 65536 --nnz-per-row 8 --iters 500
run_logged "$log/1_baseline/spmv_profile_permuted.log" \
    "$baseline" --pattern permuted --rows 65536 --nnz-per-row 8 --iters 500

run_logged "$log/2_perf_stat/perf_stat_local.log" \
    perf stat -r 3 -e cycles,instructions,cache-misses -- "$baseline" \
    --pattern local --rows 65536 --nnz-per-row 8 --iters 500
run_logged "$log/2_perf_stat/perf_stat_permuted.log" \
    perf stat -r 3 -e cycles,instructions,cache-misses -- "$baseline" \
    --pattern permuted --rows 65536 --nnz-per-row 8 --iters 500

run_logged "$log/3_pmu_col4/profile_pmu_local.log" \
    "$pmu_col4" --pmu --pattern local --rows 65536 --nnz-per-row 8 --iters 500
run_logged "$log/3_pmu_col4/profile_pmu_permuted.log" \
    "$pmu_col4" --pmu --pattern permuted --rows 65536 --nnz-per-row 8 --iters 500

run_logged "$log/4_pmu_col16/profile_pmu_col16_local.log" \
    "$pmu_col16" --pmu --pattern local --rows 65536 --nnz-per-row 8 --iters 500
run_logged "$log/4_pmu_col16/profile_pmu_col16_permuted.log" \
    "$pmu_col16" --pmu --pattern permuted --rows 65536 --nnz-per-row 8 --iters 500

# perf record writes warnings and completion messages to stderr; redirect both
# streams so the log is complete and reproducible.
run_logged "$log/5_perf_record/perf_record_local.log" \
    perf record -g -o "$perf_dir/perf_record_local.data" -- "$baseline" \
    --pattern local --rows 65536 --nnz-per-row 8 --iters 500
run_logged "$log/5_perf_record/perf_record_permuted.log" \
    perf record -g -o "$perf_dir/perf_record_permuted.data" -- "$baseline" \
    --pattern permuted --rows 65536 --nnz-per-row 8 --iters 500

run_logged "$log/6_perf_report/perf_report_local.log" \
    perf report --stdio -i "$perf_dir/perf_record_local.data"
run_logged "$log/6_perf_report/perf_report_permuted.log" \
    perf report --stdio -i "$perf_dir/perf_record_permuted.data"
