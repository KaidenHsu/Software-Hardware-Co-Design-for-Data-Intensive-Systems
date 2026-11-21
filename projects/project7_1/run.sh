#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG="$ROOT/run.log"

# Start a fresh log for each run.
: > "$LOG"

# Record a shell-escaped command, then stream its combined output.
run_logged() {
  {
    # Separate successive command blocks with three blank lines.
    if [[ -s "$LOG" ]]; then
      printf '\n\n\n'
    fi

    printf '$'
    printf ' %q' "$@"
    printf '\n'
  } >> "$LOG"

  "$@" 2>&1 | tee -a "$LOG"
}

if ! command -v verilator >/dev/null 2>&1; then
  echo 'ERROR: Verilator 5.x is required; run `verilator --version` to check.' | tee -a "$LOG" >&2
  exit 127
fi

mkdir -p "$ROOT/build"
run_logged verilator --binary --timing -Wno-fatal --top-module tb_scheduler \
  --Mdir "$ROOT/build" -j 2 \
  "$ROOT/rtl/dual_issue_scheduler.sv" "$ROOT/tb/tb_scheduler.sv"
run_logged "$ROOT/build/Vtb_scheduler"
