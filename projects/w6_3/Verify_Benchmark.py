#!/usr/bin/env python3
"""Compile and independently check the SPMM reference kernel and both layout modes."""
from pathlib import Path
import subprocess, re, sys

# Resolve paths relative to this script so it can be launched from any directory.
p = Path(__file__).resolve().parent
source = p / 'src' / 'SpMM_GNN_Aggregation_Benchmark.cpp'
binary = p / 'build' / 'spmm_gnn'
binary.parent.mkdir(parents=True, exist_ok=True)


def run(command):
    # Capture diagnostics and stop immediately if compilation or execution fails.
    r = subprocess.run(command, cwd=p, text=True, capture_output=True, timeout=240)
    if r.returncode:
        raise SystemExit('COMMAND FAILED: ' + ' '.join(map(str, command)) + '\n' + r.stdout + '\n' + r.stderr)
    return r.stdout


# 1. Build the optimized C++17 benchmark; treat compiler warnings as errors.
# -fno-omit-frame-pointer: Keeps stack frame pointers, making stack traces and profiling call stacks easier to reconstruct. It can add a small performance cost.
# -Wall:	               Enables a broad set of common compiler warnings. Despite its name, it does not enable every warning.
# -Wextra:	               Enables additional warnings beyond those enabled by -Wall.
# -Wpedantic:              Warns about language extensions and constructs that do not follow the selected ISO C++ standard.
# -Werror:	               Treats enabled warnings as errors, so compilation fails if any are reported.
run(['g++', '-O3', '-g', '-fno-omit-frame-pointer', '-std=c++17', '-Wall', '-Wextra', '-Wpedantic', '-Werror', str(source), '-o', str(binary)])

# 2. The C++ self-test checks a tiny CSR example against a hand-computed answer.
s = run([str(binary), '--selftest'])
assert 'SELFTEST=PASS' in s, s

# 3. Use a smaller workload for validation, keeping dimensions equal across layouts.
# Each run also checks every output element against its logical-data oracle.
args = ['--rows', '8192', '--nnz-per-row', '8', '--features', '8', '--iters', '3']
a = run([str(binary), '--pattern', 'local'] + args)
b = run([str(binary), '--pattern', 'permuted'] + args)
assert 'CORRECT=PASS' in a and 'CORRECT=PASS' in b

# Relocating features and indices must preserve the reported output checksum.
# This comparison supplements the full element-by-element checks inside C++.
match = lambda s: re.search(r'\bchecksum=([^\s]+)', s).group(1)
assert match(a) == match(b), (a, b)

# Hardware counters are optional and are not exercised by these checks.
print('SELFTEST=PASS')
print('LAYOUT_ORACLE=PASS checksum=' + match(a))
print('VALIDATION=PASS (PMU hardware availability must be checked on target CPU)')
