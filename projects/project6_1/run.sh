#!/usr/bin/env bash
# Week 9 handout: run on server1 using your own authorized course account.
# Usage: bash run.sh
set -eo pipefail

# Write a fresh transcript beside this script on each run.
PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
LOG="$PROJECT_DIR/run.log"
exec > "$LOG" 2>&1
COMMAND_OUTPUT=$(mktemp)
trap 'rm -f -- "$COMMAND_OUTPUT"' EXIT
first_command=1

run() {
    if (( first_command )); then
        first_command=0
    else
        printf '\n\n\n'
    fi
    # Shell-escaped arguments make the displayed command reproducible.
    printf '$ %q' "$1"
    shift
    if (( $# )); then printf ' %q' "$@"; fi
    printf '\n\n'
}

run_command() {
    local status=0
    run "$@"
    # Execute in this shell so source/export retain their effects.
    "$@" > "$COMMAND_OUTPUT" 2>&1 || status=$?
    cat "$COMMAND_OUTPUT"
    # End nonempty output with one newline before the three blank lines.
    if [[ -s "$COMMAND_OUTPUT" ]] && [[ $(tail -c 1 "$COMMAND_OUTPUT" | wc -l) -eq 0 ]]; then
        printf '\n'
    fi
    return "$status"
}

# Enable the provided compiler; do not install/rebuild the course simulators.
run_command source /opt/rh/gcc-toolset-13/enable
set -u
# Load project paths and interpreter settings in this shell.
run_command source "$PROJECT_DIR/config/default.env"
run_command mkdir -p "$ROOT/results"

# Check tool availability
run_command sha256sum "$PROJECT_DIR/config/default.env" "$PROJECT_DIR"/scripts/*.py \
  "$PROJECT_DIR"/rtl/*.sv "$PROJECT_DIR"/tb/*.sv "$PROJECT_DIR"/templates/*.py
run_command "$PY" --version
run_command g++ --version
run_command verilator --version

# Run self test
run_command "$PY" "$W9" --selftest

# Generate only the tiny oracle and compulsory medium workload.
run_command "$PY" "$W9" --make --tiny --out "$ROOT/results/tiny"
run_command "$PY" "$W9" --make --rows 1024 --nnz-per-row 8 \
  --cols 4096 --pattern scattered --tile 2048 \
  --out "$ROOT/results/medium"

# Controlled DRAM row/bank experiments (synthetic controller replays).
run_command "$PY" "$W9" --dram-hierarchy --out "$ROOT/results/medium"
run_command cat "$ROOT/results/medium/reports/dram_stats/w9_dram_sequential_16B.ramulator_metrics.json"
run_command cat "$ROOT/results/medium/reports/dram_stats/w9_dram_strided_16B.ramulator_metrics.json"

# Boundary-aware integer operations per DMA byte.
run_command "$PY" "$W9" --roofline --out "$ROOT/results/medium"
run_command cat "$ROOT/results/medium/reports/w9_roofline_intensity_proxy.json"

# Actual RTL smoke test and file-driven full-output/backpressure test.
run_command "$PY" "$W9" --out "$ROOT/results/tiny" --verilator
run_command "$PY" "$W9" --out "$ROOT/results/medium" --verilator-full

# Section 7: reproduce the synthetic tiled-DMA DDR3 feasibility replay.
run_command "$PY" "$W9" --ramulator --out "$ROOT/results/medium"
run_command cat "$ROOT/results/medium/reports/dram_stats/tiled_dma_16B.ramulator_metrics.json"
