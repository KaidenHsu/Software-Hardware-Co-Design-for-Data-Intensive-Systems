#!/usr/bin/env python3
"""Build the reference benchmark and verify both deterministic layouts."""

from pathlib import Path
import re
import subprocess


# Resolve paths from the repository root so this script works from any cwd.
PROJECT_ROOT = Path(__file__).resolve().parent.parent
SOURCE = PROJECT_ROOT / "src" / "SpMV_Guided_Benchmark.cpp"
BUILD_DIR = PROJECT_ROOT / "build"
BINARY = BUILD_DIR / "spmv_bench"


def run(command: list[str]) -> str:
    """Run a command and turn any non-zero exit into a useful failure."""

    result = subprocess.run(
        command, cwd=PROJECT_ROOT, text=True, capture_output=True,
        timeout=240, check=False,
    )

    if result.returncode:
        rendered = " ".join(map(str, command))
        raise SystemExit(
            f"COMMAND FAILED: {rendered}\n{result.stdout}\n{result.stderr}"
        )

    return result.stdout


def checksum(output: str) -> str:
    """Extract the benchmark checksum used to compare the two layouts."""

    match = re.search(r"\bchecksum=([^\s]+)", output)
    if match is None:
        raise AssertionError(f"Benchmark output has no checksum: {output}")

    return match.group(1)


def main() -> None:
    """Compile the benchmark, run its self-test, and compare both layouts."""

    BUILD_DIR.mkdir(parents=True, exist_ok=True)

    # Compile benchmark with strict warnings
    run([
        "g++", "-O3", "-g", "-fno-omit-frame-pointer", "-std=c++17",
        "-Wall", "-Wextra", "-Wpedantic", "-Werror",
        str(SOURCE), "-o", str(BINARY),
    ])

    selftest = run([str(BINARY), "--selftest"])
    assert "SELFTEST=PASS" in selftest, selftest

    # Both runs use the same workload; only the memory layout changes.
    common_args = ["--rows", "8192", "--nnz-per-row", "8", "--iters", "3"]
    local = run([str(BINARY), "--pattern", "local", *common_args])
    permuted = run([str(BINARY), "--pattern", "permuted", *common_args])
    assert "CORRECT=PASS" in local and "CORRECT=PASS" in permuted

    # Verify two checksums of two runs are the same
    local_checksum = checksum(local)
    assert local_checksum == checksum(permuted), (local, permuted)

    print("SELFTEST=PASS")
    print(f"LAYOUT_ORACLE=PASS checksum={local_checksum}")
    print("VALIDATION=PASS (PMU hardware availability must be checked on target CPU)")


if __name__ == "__main__":
    main()
