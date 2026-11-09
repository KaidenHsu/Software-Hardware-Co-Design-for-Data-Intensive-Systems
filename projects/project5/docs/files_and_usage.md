# Files and Usage

This guide covers operating the experiment and locating its sources, logs, and
outputs. Start with the [Introduction and Quick Start](../README.md) for the
experiment overview and stage table. Commands below run from the project root.

## Configuration and Requirements

[config/default.env](../config/default.env) supplies the handout's server1 defaults:

```bash
PY=/home/asinha/tools/week8/venv/bin/python
GEM5_ROOT=/home/asinha/gem5
RAM_ROOT=/home/asinha/tools/week8/ramulator2
GCC_ENABLE=/opt/rh/gcc-toolset-13/enable
```

Edit that file for your machine, or override settings per invocation:

```bash
PY=/path/to/python GEM5_ROOT=/path/to/gem5 ./run.sh --stage check
GCC_ENABLE= ./run.sh --help             # Skip compiler setup if already configured
./run.sh --gem5-root /path/to/gem5 --ramulator-root /path/to/ramulator --stage check
```

The runner sources shell variables, uses `PY` to select Python, and passes tool
paths as arguments. They do not need `export` in the configuration file. The GCC
setup script establishes its own environment for compiler subprocesses. Execute
the runner (`./run.sh` or `bash run.sh`); do not source it.

Requirements: Python 3.10+, the supplied `ramulator` and `yaml` packages, gem5
v25.1 x86 with **prebuilt** `libm5.a`, Ramulator 2.1 with the local
`W8_DRAIN_CALLBACK_PATCH_V1`, GCC with static-link support. The `check` stage
records tool paths/versions, gem5 commit,
Python interpreter, source hash and drain-patch hash in `environment.json`.
It does not use gem5's unsupported `--version` option. No sudo, installation,
instructor credentials or builds inside shared tool directories are needed.

## Selecting Stages and Workloads

Use `--stage` for one stage or `--from`/`--to` for an inclusive range. These
options cannot be combined. Required outputs must already be valid; omitted
prerequisite stages are not executed automatically. Since the shell runner
clears default outputs, a fresh partial run must include its prerequisites.

```bash
# Fresh setup and guest compilation, without simulation.
./run.sh --to build

# Preview a stage range without clearing outputs or running it.
./run.sh --from gem5 --to payload --dry-run

# Single-pattern evidence; final report will be PARTIAL.
./run.sh --pattern scattered

# Smaller end-to-end integration experiment.
./run.sh --rows 4096
```

Defaults: `--rows 32768 --nnz-per-row 16 --cols 262144 --pattern both`.
Harness limits: rows 1–1,000,000; nonzeros/row 1–64; columns 4,096–10,000,000;
arrays at most 96 MiB. Tiny workloads may fail trace validation because warmed
caches yield fewer than 256 post-L2 requests, even when the arithmetic is correct.

Compiled binaries live in the project-root `build/` directory, independently of
`--results-dir`.

Other flags: `--results-dir`, `--gem5-timeout` (7200 seconds by default),
`--replay-timeout` (3600 seconds), `--dry-run` and `--help`.

```bash
./run.sh --stage check                 # Fresh tool check only
./run.sh --help                        # Show all options without clearing outputs
```

## Fresh Runs and Continuing an Experiment

`run.sh` starts executing invocations by removing the project-root `build/`,
`logs/`, and `results/`, then starts the requested stages. This also applies to
`--stage`, `--from`, `--to`, and `--resume`: stage prerequisites are not run
automatically, and `--resume` cannot recover deleted default outputs. For a fresh
partial run, use a range beginning early enough to produce its prerequisites,
such as `./run.sh --to build`. Help and dry-run skip cleanup. Every shell
invocation still overwrites `run.log` with its invocation and runner output.

Cleanup targets only those three project-root directories, even when
`--results-dir` selects another location. An external results directory is not
removed, but project-root binaries are still removed, so it should not be used
to circumvent fresh-run behavior. Use one active runner per project; cleanup
happens before the Python results-directory lock is acquired.

To continue retained work without cleanup, call the Python coordinator directly
from the project root in an environment with the required compiler and libraries
already configured. For the supplied server installation:

```bash
/home/asinha/tools/week8/venv/bin/python scripts/run_experiments.py --resume
/home/asinha/tools/week8/venv/bin/python scripts/run_experiments.py --stage replay
```

Direct invocation does not load `config/default.env`, source compiler setup, or
capture runner output into `run.log`; consolidated stage logs are still written.
Pass simulator paths explicitly if the Python CLI defaults do not match your
installation. Only direct invocations can inherit the retained configuration
and reuse default-directory outputs across runs.

The manifest records stage states, configuration, artifact hashes, and logs.
`--resume` skips only stages whose inputs, outputs, and prerequisites validate.
Rerunning upstream stages marks dependent records stale. Changed source files
or tool metadata also invalidate reuse. Errors record FAILED and stop execution.

Source hashes record provenance rather than enforce the handout's distribution
hash. The tool check records the current reference hash, generation snapshots
the exact source compiled, and replay verification records that snapshot's hash.
Formatting changes do not fail preflight, but source edits still invalidate
resume eligibility. Numerical oracle checks remain mandatory.

The build stage does not define `W8_NATIVE_TEST` or compile/run a native smoke
executable. `build/spmv_large_gem5` retains real gem5 marker instructions and
must run inside gem5. The separate Week 7 baseline still runs on the host;
the larger workload is checked against its reference after the gem5 ROI.

## Direct Replay

The original backend can still be called directly:

```bash
/home/asinha/tools/week8/venv/bin/python scripts/replay_request_equivalent.py \
    results/scattered/trace/spmv_roi_postL2.trace \
    --out-dir results/manual-replay
```

Standalone backend calls do not update the pipeline manifest or perform the
runner's full completion audit. Use the staged runner for tracked evidence.

## Trace Filtering and Replay Validation

Trace extraction selects post-L2 requests whose timestamps fall in `[start,end)`
from [roi_window.json](../results/scattered/gem5/roi_window.json). This is traffic
crossing L2, not every CPU load: instruction traffic and requests overlapping ROI
boundaries may be present, and requests issued near the end may complete later.
Inspect [kernel_trace_manifest.json](../results/scattered/trace/kernel_trace_manifest.json)
for command counts, size histograms, timing, and the exported trace hash.

The `replay` stage preserves one request per exported record; the `payload` stage
represents each original 64-byte packet as one 64-byte DDR4 request or two
adjacent 32-byte HBM2 requests. Replays discard the original gem5 timestamps and
packet sizes from their input stream and use normalized request injection.
Completion callbacks and accepted/served counts, including forwarded reads and
coalesced writes, must reconcile with zero outstanding requests. Inspect the
backend command blocks in [request-equivalent stage log](../logs/6_replay_req_equiv_ramulator_trace.log) and
[byte-equivalent stage log](../logs/7_replay_byte_equiv_ramulator_trace.log), together with per-case verification files.

## Timing Units and Model Assumptions

Modeled controller time is `cycles × tCK(ps) / 10^9` milliseconds. The payload
replay assumes 833 ps for DDR4 and 1000 ps for HBM2; recheck installed timing
presets when changing simulator installations. The values and results are
recorded in [payload_equivalent_summary.json](../results/payload_equivalent_summary.json).
Controller cycles are not nanoseconds, and controller replay time must remain
separate from gem5 ROI execution time when reading the report.

## Project Structure

| Path | Responsibility |
|---|---|
| [run.sh](../run.sh) | Load machine/compiler settings and launch Python |
| [config/default.env](../config/default.env) | Read-only installation paths |
| [scripts/run_experiments.py](../scripts/run_experiments.py) | CLI, dependencies, run tracking, locking and resume |
| [scripts/experiment_stages.py](../scripts/experiment_stages.py) | Checks, baseline, generation, compilation, gem5, trace extraction, request-equivalent replay audit and byte-equivalent stage wrapper |
| [scripts/replay_request_equivalent.py](../scripts/replay_request_equivalent.py) | Original request-equivalent DDR4/HBM2 replay |
| [scripts/replay_byte_equivalent.py](../scripts/replay_byte_equivalent.py) | Byte-equivalent transformation, replay and completion accounting |
| [scripts/generate_report.py](../scripts/generate_report.py) | Evidence validation, tables and ratios |
| [templates/csr_spmv_large_roi.cpp](../templates/csr_spmv_large_roi.cpp) | Large input generator and kernel-only C++ harness |
| [templates/gem5_kernel_roi.py](../templates/gem5_kernel_roi.py) | CPU/cache/DDR4 configuration, probe and ROI events |
| [src/week7_spmv_lab.cpp](../src/week7_spmv_lab.cpp) | Canonical formatted Week 7 reference used by the baseline and ROI harness |

The former root-level Python scripts are refactored into these modules. The
embedded C++ and gem5 strings are now separate, commented template files. Each
experiment snapshots the templates and verified oracle before compiling them.
Comments/section headings explain setup, measurement, validation and accounting.
The reference keeps the Week 7 computation; only whitespace differs from the
classroom original. The runner records the actual source hash for reproducibility,
rather than rejecting edits against a fixed expected hash.

## Output Layout

```text
build/                                 # Baseline and gem5 guest binaries
results/
├── run_manifest.json
├── environment.json
├── generated/                         # Templates and canonical reference snapshot
├── scattered/                         # clustered/ has the same structure
│   ├── gem5/                          # Raw protobuf, ROI window, stats and config
│   ├── gem5_kernel_roi_stats.txt       # ROI section only
│   ├── trace/                         # LD/ST trace and kernel_trace_manifest.json
│   ├── replay_req_equiv/               # DDR4/HBM2 stats and input manifest
│   ├── kernel_profile_verification.json
│   └── replay_byte_equiv/                # Split trace, stats, logs and verification.json
├── clustered/
├── payload_equivalent_summary.json
└── report/
    ├── summary.json
    └── report.md
```

Stage logs live beside results, not inside generated artifacts. Each stage now
writes one numbered file containing its invocation, Python diagnostics, and all
external commands in execution order. CLI stage names remain unchanged:

```text
logs/
├── 0_check_tools.log
├── 1_check_correctness.log
├── 2_snapshot_gem5_sources.log
├── 3_compile_workload.log
├── 4_simulate_gem5.log
├── 5_extract_roi_trace.log
├── 6_replay_req_equiv_ramulator_trace.log
├── 7_replay_byte_equiv_ramulator_trace.log
└── 8_generate_report.log
run.log                    # Runner stdout/stderr, teed to the terminal
```

This layout applies to future executions. Existing per-stage folders and their
manifest records are retained as historical evidence until an executing shell
invocation clears the output directories. Links in the detailed results report
continue to reference those historical files; no consolidation was performed.

Each command block starts with a shell-quoted command and a blank line, followed
by combined stdout/stderr. Exactly three blank lines separate successive blocks:

```text
$ <command>

<output and error>



$ <next command>

<output and error>
```

During execution the terminal shows command announcements without a `$` prefix;
command output and Python diagnostics stay in the consolidated stage log.
Failures identify that same file. Each executed stage replaces its previous log
once, then appends commands; a stage skipped by `--resume` retains its log.
Manifest hashes are computed after the log is closed and include it only once.

For direct byte-equivalent replay, `--log-file /path/to/stage.log` appends all
backend command blocks to one file. The older `--log-dir /path/to/logs` option
still selects separate backend logs. The options are mutually exclusive. The
coordinator supplies `--log-file` and handles resetting its stage log.

Help and dry-run preserve experiment directories. Each shell invocation still
overwrites project-root `run.log`; executing invocations first remove
project-root `build/`, `logs/`, and `results/`. Direct Python invocations preserve
existing directories and replace only logs for executed stages. There are no
attempt directories. `tee` preserves nonzero runner exit status. With
`--results-dir /some/path/results`, stage logs go to `/some/path/logs`.

The guest build keeps real gem5 ROI markers enabled; there is no native smoke
build or `-DW8_NATIVE_TEST` compiler flag. The Week 7 baseline remains a host
correctness check. See [fresh-run and continuation behavior](#fresh-runs-and-continuing-an-experiment)
for the effect of cleanup on stage selection and resume.

The report is COMPLETE only for both patterns with valid check, baseline,
and original-replay evidence. Otherwise it explicitly says PARTIAL. The
handout's written predictions, explanations and conclusions remain student work;
the report generates evidence, not invented analysis or instructor reference data.

The project-root `run.log` starts with `$ bash run.sh <arguments>` and a blank
line, followed by runner stdout/stderr. Command announcements in that output
have no `$` prefix; command and stage log headings under `logs/` retain it.
