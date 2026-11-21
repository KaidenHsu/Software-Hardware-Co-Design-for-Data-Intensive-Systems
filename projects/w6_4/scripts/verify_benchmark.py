#!/usr/bin/env python3
"""Compile and independently check the SPMM reference kernel and both layout modes."""

from pathlib import Path
import subprocess, re, sys

# Resolve paths relative to this script so it works from any working directory.
p=Path(__file__).resolve().parent.parent
source=p/'src'/'SpMM_GNN_Aggregation_Benchmark.cpp'
binary=p/'build'/'spmm_gnn'
build_log_path=p/'results'/'1_build'/'build.log'
build_log_path.parent.mkdir(parents=True,exist_ok=True)
build_log_path.write_text('')
# Create the output directory on a fresh checkout before invoking the compiler.
binary.parent.mkdir(parents=True,exist_ok=True)


# Run each command in the benchmark directory, capturing diagnostics on failure.
def run(command):
    r=subprocess.run(command,cwd=p,text=True,capture_output=True,timeout=240)
    with build_log_path.open('a') as log:
        log.write('$ '+' '.join(map(str,command))+'\n\n')
        log.write(r.stdout)
        if r.stderr:
            log.write('\n[stderr]\n'+r.stderr)
        log.write(f'\n[exit_code={r.returncode}]\n\n')
    if r.returncode: raise SystemExit('COMMAND FAILED: '+' '.join(map(str,command))+'\n'+r.stdout+'\n'+r.stderr)
    return r.stdout


# Build the benchmark with optimization, debug information, and strict warnings.
run(['g++','-O3','-g','-fno-omit-frame-pointer','-std=c++17','-Wall','-Wextra','-Wpedantic','-Werror',str(source),'-o',str(binary)])

# Check the kernel's built-in tests before running the larger layout comparison.
s=run([str(binary),'--selftest'])
assert 'SELFTEST=PASS' in s,s

# Use the same workload size and iteration count for both memory layouts.
args=['--rows','8192','--nnz-per-row','8','--features','8','--iters','3']

# Each layout must pass the benchmark's independent numerical correctness check.
a=run([str(binary),'--pattern','local']+args)
b=run([str(binary),'--pattern','permuted']+args)
assert 'CORRECT=PASS' in a and 'CORRECT=PASS' in b

# Compare printed checksums to confirm both layouts produce the same total.
match=lambda s: re.search(r'\bchecksum=([^\s]+)',s).group(1)
assert match(a)==match(b),(a,b)

# Verify both PMU paths preserve the numerical oracle, even when PMU access is denied.
for flag,mode in [('--pmu','core'),('--pmu-levels','levels')]:
    pmu_output=run([str(binary),flag,'--pattern','local']+args)

    assert 'CORRECT=PASS' in pmu_output and 'PMU_MODE='+mode in pmu_output, pmu_output
    assert match(pmu_output)==match(a), (flag,pmu_output)
    # Counter availability may vary by CPU and permissions; all listed states are valid.
    assert any('PMU_STATUS='+status in pmu_output for status in ('OK','PARTIAL','UNAVAILABLE'))

# Report success only after every check above has passed. Numerical validation
# does not guarantee that hardware performance counters were available.
print('PMU_MODES=PASS')
print('SELFTEST=PASS')
print('LAYOUT_ORACLE=PASS checksum='+match(a))
print('VALIDATION=PASS (PMU hardware availability must be checked on target CPU)')

with build_log_path.open('a') as log:
    log.write('PMU_MODES=PASS\n')
    log.write('SELFTEST=PASS\n')
    log.write('LAYOUT_ORACLE=PASS checksum='+match(a)+'\n')
    log.write('VALIDATION=PASS (PMU hardware availability must be checked on target CPU)\n')
