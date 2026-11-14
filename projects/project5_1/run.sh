#!/usr/bin/env bash
# Resolve paths relative to this script, even when invoked from another directory.
# Stop on command failures and propagate failures through the tee pipeline.
set -eo pipefail

PROJECT_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

# Record the runner invocation once, then append its combined stdout/stderr.
# %q preserves argument boundaries when options contain spaces or shell syntax.
{
    printf '$ bash run.sh'
    # The zero-argument case needs no extra space after the script name.
    if (( $# )); then
        printf ' %q' "$@"
    fi
    printf '\n\n'
} > "$PROJECT_ROOT/run.log"

# Synchronous tee captures runner stdout/stderr and preserves failure exit codes.
# Command output itself is redirected by Python into logs/<stage>/*.log.
(
    # Real shell-runner invocations start fresh. Informational modes preserve data.
    CLEAN_OUTPUTS=true
    for argument in "$@"; do
        case "$argument" in
            --help|-h|--dry-run) CLEAN_OUTPUTS=false ;;
        esac
    done

    if "$CLEAN_OUTPUTS"; then
        printf 'rm -rf -- %q %q %q\n' "$PROJECT_ROOT/build" "$PROJECT_ROOT/logs" "$PROJECT_ROOT/results"
        rm -rf -- "$PROJECT_ROOT/build" "$PROJECT_ROOT/logs" "$PROJECT_ROOT/results"
    fi

    # Load shell defaults before choosing the interpreter and installed simulator paths.
    source "$PROJECT_ROOT/config/default.env"

    # Compiler setup may adjust PATH and runtime library search paths for children.
    if [[ -n "$GCC_ENABLE" ]]; then
        if [[ ! -r "$GCC_ENABLE" ]]; then
            printf 'Cannot read GCC setup: %s\n' "$GCC_ENABLE" >&2
            exit 1
        fi
        source "$GCC_ENABLE"
    fi

    # The system toolchain setup may reference unset variables.
    set -u

    # Replace this subshell with the coordinator; the outer shell still runs tee.
    exec "$PY" "$PROJECT_ROOT/scripts/run_experiments.py" \
        --gem5-root "$GEM5_ROOT" --ramulator-root "$RAM_ROOT" "$@"
) 2>&1 | tee -a "$PROJECT_ROOT/run.log"
