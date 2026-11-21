#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_ROOT"

mkdir -p logs evidence

run_logged() {
    local log_file="$1"
    shift

    {
        printf '$'
        printf ' %q' "$@"
        printf '\n'
        "$@"
    } >"$log_file" 2>&1
}

run_logged logs/verify_benchmark.log \
    python3 scripts/verify_benchmark.py

run_logged logs/local_layout.log \
    ./build/spmv_bench --pattern local --rows 65536 --nnz-per-row 8 --iters 500

run_logged logs/permuted_layout.log \
    ./build/spmv_bench --pattern permuted --rows 65536 --nnz-per-row 8 --iters 500

run_logged evidence/source_hashes.txt \
    sha256sum src/SpMV_Guided_Benchmark.cpp src/di_common.hpp src/di_kernel_pmu.hpp