#!/usr/bin/env python3
"""Compile and independently check the SpMV reference kernel and both layouts."""

import re
import subprocess
import sys
from pathlib import Path


# Resolve paths from the repository root so the script works from any directory.
PROJECT_ROOT = Path(__file__).resolve().parent.parent
SOURCE = PROJECT_ROOT / "src" / "SpMV_Guided_Benchmark.cpp"
BINARY = PROJECT_ROOT / "build" / "spmv_bench"


def run(command):
    """Run a command from the project root and stop with useful diagnostics."""
    result = subprocess.run(
        command,
        cwd=PROJECT_ROOT,
        text=True,
        capture_output=True,
        timeout=240,
    )

    if result.returncode:
        raise SystemExit(
            "COMMAND FAILED: "
            + " ".join(map(str, command))
            + "\n"
            + result.stdout
            + "\n"
            + result.stderr
        )

    return result.stdout


# Build the benchmark with strict warnings enabled.
BINARY.parent.mkdir(exist_ok=True)
run(
    [
        "g++",
        "-O3",
        "-g",
        "-fno-omit-frame-pointer",
        "-std=c++17",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Werror",
        str(SOURCE),
        "-o",
        str(BINARY),
    ]
)

# Run the built-in C++ self-test before measuring either layout.
selftest_output = run([str(BINARY), "--selftest"])
assert "SELFTEST=PASS" in selftest_output, selftest_output

# Use a small deterministic case for the independent layout comparison.
benchmark_args = ["--rows", "8192", "--nnz-per-row", "8", "--iters", "3"]
local_output = run([str(BINARY), "--pattern", "local"] + benchmark_args)
permuted_output = run([str(BINARY), "--pattern", "permuted"] + benchmark_args)

assert "CORRECT=PASS" in local_output and "CORRECT=PASS" in permuted_output


def checksum(output):
    """Extract the benchmark checksum from one command's output."""
    return re.search(r"\bchecksum=([^\s]+)", output).group(1)


assert checksum(local_output) == checksum(permuted_output)

# Verify both PMU paths preserve the numerical oracle, even when PMU access is denied.
for flag, mode in [("--pmu", "core"), ("--pmu-levels", "levels")]:
    pmu_output = run([str(BINARY), flag, "--pattern", "local"] + benchmark_args)

    assert "CORRECT=PASS" in pmu_output
    assert "PMU_MODE=" + mode in pmu_output, pmu_output
    assert checksum(pmu_output) == checksum(local_output), pmu_output
    assert any(
        "PMU_STATUS=" + status in pmu_output
        for status in ("OK", "PARTIAL", "UNAVAILABLE")
    )

print("PMU_MODES=PASS")
print("SELFTEST=PASS")
print("LAYOUT_ORACLE=PASS checksum=" + checksum(local_output))
print("VALIDATION=PASS (PMU hardware availability must be checked on target CPU)")

