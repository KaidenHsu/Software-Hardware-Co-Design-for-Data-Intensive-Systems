# Reading Guide: From the Framework to Generated Evidence

This experiment asks how input locality changes CSR SpMV execution and memory
traffic, and how that traffic behaves in standalone DDR4 and HBM2 models.
Scattered and clustered inputs have the same dimensions and nonzero count, but
use different ranges of indices into `x`. Numerical results are checked against
the reference computation for each input.

Read in the order below. Follow one case, `scattered`, through the files first;
then compare it with `clustered`. All paths are relative to this project root.
The paths shown use the default [results/](../results) directory.

## Reading Order

| Order | Read | Question to answer |
|---|---|---|
| 1 | [run.sh](../run.sh), [config/default.env](../config/default.env) | How does a run start, select tools, and capture output? |
| 2 | [scripts/run_experiments.py](../scripts/run_experiments.py) | How are stages selected, called, and tracked? |
| 3 | [scripts/experiment_stages.py](../scripts/experiment_stages.py): helpers, `check_stage`, `baseline_stage` | How are commands logged and correctness established? |
| 4 | [src/week7_spmv_lab.cpp](../src/week7_spmv_lab.cpp) | What computation is the reference? |
| 5 | [templates/csr_spmv_large_roi.cpp](../templates/csr_spmv_large_roi.cpp), [templates/gem5_kernel_roi.py](../templates/gem5_kernel_roi.py) | What workload and simulated machine are measured? |
| 6 | `generate_stage` and `build_stage` in [experiment_stages.py](../scripts/experiment_stages.py) | How do source files become a recorded snapshot and executable binaries? |
| 7 | `gem5_stage`, `extract_roi_packets`, and `trace_stage` in [experiment_stages.py](../scripts/experiment_stages.py) | How does execution become a replayable memory trace? |
| 8 | `replay_stage` and [scripts/replay_request_equivalent.py](../scripts/replay_request_equivalent.py) | What happens when each model receives the same number of requests? |
| 9 | `payload_stage` in [experiment_stages.py](../scripts/experiment_stages.py) and [scripts/replay_byte_equivalent.py](../scripts/replay_byte_equivalent.py) | How is the comparison adjusted to equal logical byte counts? |
| 10 | [scripts/generate_report.py](../scripts/generate_report.py) | Which evidence reaches the report, and what can it establish? |

Use [README.md](../README.md) for commands and assumptions, and
[docs/files_and_usage.md](files_and_usage.md) as a directory reference. The course handout in
[docs/handout.pdf](handout.pdf) supplies assignment context.

## 1. Start at the Shell Boundary

Read [run.sh](../run.sh) from top to bottom alongside [config/default.env](../config/default.env).
`PROJECT_ROOT` is resolved from the script location, so launching it from another
working directory does not change its project paths. Configuration selects the
Python interpreter, gem5 and Ramulator installations, and an optional compiler
setup script. Environment variables can override the supplied defaults.

The `{ ...; }` block writes the invocation header into [run.log](../run.log). The `( ... )`
block runs configuration loading and Python startup in a subshell. `exec`
replaces that subshell with Python. `2>&1` combines stdout and stderr; `tee -a`
copies that stream to the terminal and appends it to [run.log](../run.log). `pipefail`
prevents a successful `tee` from hiding a failed Python process.

**Look at [run.log](../run.log) now.** Its first lines should resemble:

```text
$ bash run.sh --stage check

/path/to/python /path/to/scripts/run_experiments.py ...
g++ --version
```

Only command announcements normally appear after the header. Each stage now
collects its invocation, diagnostics, and external-command output in one file
under [logs/](../logs). `LOG_FILES` in
[experiment_stages.py](../scripts/experiment_stages.py) defines the numbered names.
Each command block uses `$ <command>`, a blank line, and combined stdout/stderr;
exactly three blank lines separate blocks. The stage log is reset once when the
stage executes and retained when resume skips it.

This guide uses the new paths for future executions. Existing log folders and
manifest paths are historical evidence and have not been migrated. The
[detailed results report](experiment_result.md) keeps links to that evidence.
Repeated links below can now point to the same file: find the relevant command
heading within it rather than opening a separate command log.

Executing [run.sh](../run.sh) first removes project-root [build/](../build), [logs/](../logs), and [results/](../results).
Help and dry-run preserve them. Thus a shell invocation starts fresh, and
`--resume` through that wrapper cannot reuse deleted default outputs. Use the
Python coordinator directly in a configured environment to continue retained
work, as described in the [Files and Usage](files_and_usage.md#fresh-runs-and-continuing-an-experiment). Each shell invocation overwrites [run.log](../run.log).
Reading files is enough for this walkthrough. Even invoking the shell runner
with `--dry-run` overwrites [run.log](../run.log), although the Python dry-run itself writes
no experiment artifacts.

## 2. Read the Coordinator Before the Stage Implementations

In [scripts/run_experiments.py](../scripts/run_experiments.py), start with these three definitions:

- `STAGES` gives the default execution order.
- `DEPS` lists the outputs that must already be valid before a stage executes.
- `FUNCTIONS` maps a stage name to its implementing Python function. All stages
  through `payload` live in [experiment_stages.py](../scripts/experiment_stages.py);
  `report` is implemented in [generate_report.py](../scripts/generate_report.py).

The dependency graph is:

```text
check                       baseline

generate → build → gem5 → trace ─┬→ replay
                               └→ payload → report
```

`check` and `baseline` are independent stages. `report` also inspects their
validity and the original replay evidence when deciding whether its final status
is COMPLETE. They are not automatic prerequisites in `DEPS`.

Next read `main()`. It parses options, fills omitted workload values from the
previous configuration or defaults, validates workload limits, and chooses a
single stage or an inclusive `--from`/`--to` range. Selecting a stage does not
execute omitted prerequisites automatically.

Then read `Experiment.__init__()` and `Experiment.execute()`. The object created
as `ctx` bundles `args`, project/results/log paths, selected patterns, and the
manifest. The coordinator calls `FUNCTIONS[stage](../self)`; that same object is
called `ctx` inside stage functions. No import of the coordinator is needed to
access the passed object's attributes.

Finally read `configure()`, `signature()`, `valid()`, and `invalidate()`.
When the Python coordinator is invoked directly to preserve outputs,
`--resume` needs more than an old PASS label: the current input fingerprint,
recorded output hashes, and prerequisite evidence must validate. Source changes,
including comments in fingerprinted code, can prevent reuse.

**Open [results/run_manifest.json](../results/run_manifest.json) now.** Match one
stage record to `execute()`: find its status, timestamps, signature, and output
hashes. Output paths are relative to [results/](../results), so `../build/...` and
`../logs/...` refer to directories beside it. `schema_version` labels the JSON
format; the runner currently does not enforce or migrate that version.

The current code uses [results/.run_experiments.lock](../results/.run_experiments.lock) for an exclusive OS lock.
The empty file can remain after the process exits; its existence does not mean
the lock is held. This lock protects one results directory. Because binaries
live in the shared project-root [build/](../build), use one active run per project even
when selecting different results directories.

## 3. Understand the Shared Helpers and Establish Correctness

In [scripts/experiment_stages.py](../scripts/experiment_stages.py), read `run()`, `check()`, `sha256()`, and
`save_json()` before the stage functions.

`run()` passes an argument list directly to `subprocess.run()`. `shlex.join()`
only formats a readable command for the log; it is not how the command executes.
`COMMAND_STREAM` preserves the original stdout so announcements remain visible
while stage diagnostics are redirected. Commands have timeouts, and a nonzero
exit fails the stage. `sha256()` fingerprints file contents; `save_json()` writes
JSON through a temporary file and atomically replaces the destination.

Read `check_stage()` next. It verifies installed tools and packages and the
Ramulator drain patch, then records the environment.

**Inspect [logs/0_check_tools.log](../logs/0_check_tools.log) and
[results/environment.json](../results/environment.json).** Compare the tool/version
record with the code. [environment.json](../results/environment.json) records a check; changing it does not
configure the environment.

Read `baseline_stage()` alongside [src/week7_spmv_lab.cpp](../src/week7_spmv_lab.cpp). Locate `Ints`,
`validate_csr()`, `csr_spmv()`, and the reference example/oracle. This is the
correctness basis reused by the larger workload.

**Inspect [logs/1_check_correctness.log](../logs/1_check_correctness.log).** The compilation block explains how
[build/week7_baseline](../build/week7_baseline) was compiled; the execution block should contain `ORACLE = PASS`.
This checks the reference example before studying larger inputs.

## 4. Read the Two Templates as the Experiment Definition

Start with [templates/csr_spmv_large_roi.cpp](../templates/csr_spmv_large_roi.cpp). It includes the reference source
while renaming its `main`, allowing it to reuse helpers and provide a different
entry point. Follow argument parsing, allocation, deterministic data generation,
the measured loop, and the final oracle in that order.

The clustered case restricts column indices to 2048 entries of `x`; the scattered
case spans `cols`. Both use the same value-generation rule and nonzero count.
Their matrices differ, so compare each output with its own reference result,
rather than expecting the two cases to have identical output vectors.

Only the call to `csr_spmv_kernel_only()` sits between `m5_work_begin()` and
`m5_work_end()`. Allocation, initialization, and reference verification happen
outside that region of interest (ROI). The measured interval includes the
kernel's CPU and cache behavior. The build does not define `W8_NATIVE_TEST`, so
real gem5 marker instructions remain active. The optional no-op branch remains
in the source but is not used by the framework.

Next read [templates/gem5_kernel_roi.py](../templates/gem5_kernel_roi.py). Follow the CPU/cache hierarchy, monitor
after L2, DDR4 controller, guest process setup, and work-item event handling.
It records ROI ticks and dumps statistics at the measurement boundary. The raw
trace spans the run; a later stage selects the ROI requests.

If the C++ template shows unresolved names in an editor, note that
[week7_spmv_lab.cpp](../src/week7_spmv_lab.cpp) lives in [src/](../src), not beside the template. The generated
snapshot places them together. Include paths and native/guest preprocessor
settings matter when analyzing this file outside its normal build command.

## 5. Follow Templates Into Generated Sources and Binaries

Return to `generate_stage()` in [experiment_stages.py](../scripts/experiment_stages.py). It copies files without
substituting template variables. Workload dimensions are runtime arguments.

| Generated path | Origin or purpose |
|---|---|
| [results/generated/csr_spmv_large_roi.cpp](../results/generated/csr_spmv_large_roi.cpp) | Copy of the C++ template |
| [results/generated/gem5_kernel_roi.py](../results/generated/gem5_kernel_roi.py) | Copy of the gem5 template |
| [results/generated/week7_spmv_lab.cpp](../results/generated/week7_spmv_lab.cpp) | Copy of the reference source |
| [results/generated/source_manifest.json](../results/generated/source_manifest.json) | Records source identity and hashes of the three copied files |

**Open [source_manifest.json](../results/generated/source_manifest.json) and [logs/2_snapshot_gem5_sources.log](../logs/2_snapshot_gem5_sources.log).**
This stage works inside Python, so its log can contain just the invocation
header; there is no compiler command to find here.
The snapshot establishes what later compilation consumed. Edit source files in
[templates/](../templates) or [src/](../src); a later generation run overwrites the copied files.

Now read `build_stage()`. It compiles the generated C++ once into
[build/spmv_large_gem5](../build/spmv_large_gem5), linked with `libm5.a`, without `-DW8_NATIVE_TEST`.
This guest executable must run inside gem5; do not execute it on the host.
There is no native smoke executable or native compile/run log.

**Inspect [logs/3_compile_workload.log](../logs/3_compile_workload.log).** Find the
gem5 include path, `libm5.a`, and `-o` destination, and confirm the absence of
`-DW8_NATIVE_TEST`. Larger-workload correctness is checked after the measured
region when this guest runs in gem5; inspect that oracle in the next section.

## 6. Follow Guest Execution Into a Filtered Memory Trace

The files described from this section onward appear after their stages execute;
they may not exist in a partially completed experiment.

Read `gem5_stage()`. It launches the installed gem5 executable with the generated
Python configuration and [build/spmv_large_gem5](../build/spmv_large_gem5), sequentially for each pattern.

**After a simulation, read [logs/4_simulate_gem5.log](../logs/4_simulate_gem5.log).** Locate
`W8_START_EVENT: workbegin`, `W8_END_EVENT: workend`, and the final numerical
oracle. The scattered and clustered commands share this file. If the stage
fails, inspect the traceback and preceding command block there.

In [results/scattered/](../results/scattered), inspect these outputs in order:

1. [gem5/config.ini](../results/scattered/gem5/config.ini): the instantiated simulated hardware.
2. [gem5/roi_window.json](../results/scattered/gem5/roi_window.json): measurement start/end ticks and tick frequency.
3. [gem5_kernel_roi_stats.txt](../results/scattered/gem5_kernel_roi_stats.txt): the extracted ROI statistics section.
4. [gem5/kernel_postL2_all.trc](../results/scattered/gem5/kernel_postL2_all.trc): the raw protobuf trace; use the decoder rather
   than treating this binary file as ordinary text.

Now read `parse_memcmd_enum()`, `extract_roi_packets()`, and `trace_stage()`.
The decoder imports gem5's protobuf utilities, maps request command numbers,
selects requests whose ticks fall in `[start,end)`, and writes `LD`/`ST` records.
Counters audit commands, packet sizes, and excluded traffic. Unexpected command
classes or insufficient traffic fail validation.

**Inspect [logs/5_extract_roi_trace.log](../logs/5_extract_roi_trace.log), then
[results/scattered/trace/kernel_trace_manifest.json](../results/scattered/trace/kernel_trace_manifest.json) and the first few lines of
[results/scattered/trace/spmv_roi_postL2.trace](../results/scattered/trace/spmv_roi_postL2.trace).** The manifest retains the counts,
size histogram, timing, and limitations that the simple text trace cannot carry.
The replay trace keeps operations and addresses, not original timestamps/sizes.
Post-L2 traffic is not a list of every source-level array access: caches and
instruction traffic affect what crosses this boundary.

## 7. Read the Request-Equivalent Replay

Read `replay_stage()` in [experiment_stages.py](../scripts/experiment_stages.py), then `execute()` and `main()` in
[scripts/replay_request_equivalent.py](../scripts/replay_request_equivalent.py). The wrapper launches a separate backend
invocation for each memory technology and then audits completion and statistics.
Both models receive one request for each original trace record. This preserves
request count; it does not guarantee equal transferred bytes across the models.

**Read [logs/6_replay_req_equiv_ramulator_trace.log](../logs/6_replay_req_equiv_ramulator_trace.log).**
Find the DDR4 and HBM2 command blocks, locate `W8_DRAIN_PASS`, and check that submitted
requests equal completed requests with zero outstanding. Then compare
[results/scattered/replay_req_equiv/ddr4_stats.yaml](../results/scattered/replay_req_equiv/ddr4_stats.yaml) and [hbm2_stats.yaml](../results/scattered/replay_req_equiv/hbm2_stats.yaml) with
[results/scattered/kernel_profile_verification.json](../results/scattered/kernel_profile_verification.json). Forwarded reads and
coalesced writes participate in the accounting; served counts alone are not the
whole completion check. Wrapper diagnostics appear in the same stage log.

## 8. Read the Byte-Equivalent Replay

Start at `payload_stage()` in [experiment_stages.py](../scripts/experiment_stages.py). It calls
`replay_byte_equivalent.main()` directly in the same Python process, supplying
explicit trace directories and output/log paths. A list resembling CLI arguments
here does not itself create a subprocess. The wrapper imports the replay module
inside the function because that module also uses the stage module's logging
helper; this avoids circular initialization at module import time.

Inside [scripts/replay_byte_equivalent.py](../scripts/replay_byte_equivalent.py), read `prepare()`, `run_backend()`,
`internal_backend()`, and finally the public path in `main()`.
`prepare()` requires aligned 64-byte source packets. For each address `a`, DDR4
keeps one request while HBM2 receives two requests, at `a` and `a+32`.
The resulting logical payload is 64 bytes for either model.

`run_backend()` launches this same script in a fresh process with
`--internal-backend`. That subprocess performs the Ramulator simulation;
the parent checks callback completion, controller accounting, and byte totals.

**Inspect [logs/7_replay_byte_equiv_ramulator_trace.log](../logs/7_replay_byte_equiv_ramulator_trace.log).**
Find the four backend command blocks for scattered/clustered and DDR4/HBM2,
with their completion summaries and the parent process diagnostics.
Follow those results into [results/scattered/replay_byte_equiv/](../results/scattered/replay_byte_equiv):

- [input_manifest.json](../results/scattered/replay_byte_equiv/input_manifest.json) explains the transformation and expected counts.
- [hbm2_32byte.trace](../results/scattered/replay_byte_equiv/hbm2_32byte.trace) shows the paired addresses.
- [ddr4_stats.yaml](../results/scattered/replay_byte_equiv/ddr4_stats.yaml) and [hbm2_stats.yaml](../results/scattered/replay_byte_equiv/hbm2_stats.yaml) contain model statistics.
- [verification.json](../results/scattered/replay_byte_equiv/verification.json) collects the audited results for this pattern.

Finally open [results/payload_equivalent_summary.json](../results/payload_equivalent_summary.json), which combines cases.
The modeled controller time is `cycles × tCK(ps) / 10^9` milliseconds. The script
records assumed preset clock periods; inspect them before interpreting ratios.

## 9. Read the Report and Trace Each Number Back to Evidence

Read `report_stage()` in [scripts/generate_report.py](../scripts/generate_report.py). It checks source hashes,
request/byte accounting, and replay completion before building tables. It takes
gem5 ROI timing from trace manifests and memory-model timing from the payload
summary; these are separate measurements.

**Open [logs/8_generate_report.log](../logs/8_generate_report.log), [results/report/report.md](../results/report/report.md), and
[results/report/summary.json](../results/report/summary.json).** Follow one table row backward to its payload
verification or trace manifest. COMPLETE requires both patterns and valid check,
baseline, and original-replay evidence in addition to the payload inputs needed
by this stage. PARTIAL identifies missing or stale optional evidence.

Compare scattered versus clustered gem5 time and request count to study
locality. Compare DDR4 versus HBM2 replay time to study the normalized traffic
under the selected memory models. Standalone replay discards original request
spacing and does not feed memory responses back into gem5, so its ratio is not
an end-to-end SpMV speedup or full-stack HBM bandwidth measurement.

Return to [run_manifest.json](../results/run_manifest.json) last: connect each report input to the stage that
produced it, its logs, and its retained artifact hashes. That gives you the full
path from shell invocation through framework decisions to generated evidence.
