# Experiment Results

This report expands the [README results](../README.md#5-experiment-results) with
source evidence, calculations, and observations from the recorded run. Values
describe that run; changing framework code does not retroactively rerun it.

The results below use the default workload: 32,768 rows, 16 nonzeros per row,
and 262,144 columns, for a total of 524,288 nonzeros in each case.

The evidence links below point to the consolidated stage logs. Each replay log
contains separate command blocks for the patterns and memory models; see
[Files and Usage](files_and_usage.md#output-layout) for the log layout.

## Memory Access Locality Comparison

| Pattern | gem5 ROI Time (ms) | Exported Reads | Exported Writes | Total Exported Requests | Logical Bytes (B) |
|---|---:|---:|---:|---:|---:|
| Scattered | 47.385717 | 480,956 | 2,062 | 483,018 | 30,913,152 |
| Clustered | 13.706270 | 69,776 | 1,954 | 71,730 | 4,590,720 |
| Scattered / Clustered | 3.457× | 6.893× | 1.055× | 6.734× | 6.734× |

The scattered case takes 3.46× as long as the clustered case and exports
6.73× as many requests. Most of the traffic difference comes from reads:
480,956 for scattered accesses versus 69,776 for clustered accesses.
The smaller working set in the clustered case gives the caches more opportunity
to serve accesses before they reach memory. Logical bytes count the exported
64-byte read/write requests; skipped `CleanEvict` records are excluded.

| Case | Execution Log | Trace Counts and Timing |
|---|---|---|
| Scattered | [gem5 log](../logs/4_simulate_gem5.log) | [trace manifest](../results/scattered/trace/kernel_trace_manifest.json) |
| Clustered | [gem5 log](../logs/4_simulate_gem5.log) | [trace manifest](../results/clustered/trace/kernel_trace_manifest.json) |


The clustered input reduces kernel time by 71.08% and
exported traffic by 85.15% relative to the scattered input.
The traffic ratio is larger than the runtime ratio: fewer memory requests do not
translate proportionally into total execution time, which also includes CPU and
cache activity. These observations are consistent with improved locality; the
trace counts alone do not quantify individual cache hit rates.

| ROI Trace Accounting | Scattered | Clustered |
|---|---:|---:|
| All observed ROI packets | 961,804 | 139,315 |
| Exported reads and writes | 483,018 | 71,730 |
| Skipped `CleanEvict` packets | 478,786 | 67,585 |

Exported requests plus skipped clean evictions equal all observed ROI packets.
Every exported request in this run is 64 bytes, so multiplying exported counts
by 64 gives the logical-byte column above. A clean eviction carries no dirty
writeback payload and is not exported as a Ramulator store.

## Request-equivalent Trace Replay

| Pattern | Model | Requests | Logical Bytes (B) | Controller Cycles | Modeled Time (ms) |
|---|---|---:|---:|---:|---:|
| Scattered | DDR4 | 483,018 | 30,913,152 | 2,507,545 | 2.088785 |
| Scattered | HBM2 | 483,018 | 15,456,576 | 1,344,218 | 1.344218 |
| Clustered | DDR4 | 71,730 | 4,590,720 | 382,715 | 0.318802 |
| Clustered | HBM2 | 71,730 | 2,295,360 | 107,130 | 0.107130 |

HBM2 completes the request-equivalent replay in less modeled time for both
patterns. However, each model receives the same request count while DDR4
represents 64 bytes per request and HBM2 represents 32 bytes. HBM2 therefore
handles only half the logical bytes in this comparison. The timing difference
alone cannot establish how the models compare when serving the same data volume.

| Pattern | Model | Row-buffer Hit Rate | Average Read Latency (ns) |
|---|---|---:|---:|
| Scattered | DDR4 | 25.36% | 166.235 |
| Scattered | HBM2 | 14.70% | 118.317 |
| Clustered | DDR4 | 96.77% | 163.211 |
| Clustered | HBM2 | 92.37% | 65.868 |

Both models have higher row-buffer hit rates for clustered traffic. HBM2 has
lower average read latency than DDR4 for both patterns, but its scattered hit
rate is lower than DDR4's. Row-buffer hit rate alone therefore does not explain
the latency difference. These are per-transaction averages with different
payload sizes: 64 bytes for DDR4 and 32 bytes for HBM2.

Hit rate uses `hits / (hits + misses + conflicts)`. Latency uses
`avg_read_latency_cycles × tCK(ps) / 1000` to express both models in nanoseconds,
with assumed clock periods of 833 ps for DDR4 and 1000 ps for HBM2. The values
come from the request-equivalent `replay_req_equiv` statistics linked below,
not the byte-equivalent run.

Modeled time is calculated as `cycles × tCK(ps) / 10^9`, using the experiment's
assumed clock periods of 833 ps for DDR4 and 1000 ps for HBM2. This conversion is
used for both replay comparisons; controller cycles are not nanoseconds.

| Case | DDR4 Evidence | HBM2 Evidence |
|---|---|---|
| Scattered | [log](../logs/6_replay_req_equiv_ramulator_trace.log), [statistics](../results/scattered/replay_req_equiv/ddr4_stats.yaml) | [log](../logs/6_replay_req_equiv_ramulator_trace.log), [statistics](../results/scattered/replay_req_equiv/hbm2_stats.yaml) |
| Clustered | [log](../logs/6_replay_req_equiv_ramulator_trace.log), [statistics](../results/clustered/replay_req_equiv/ddr4_stats.yaml) | [log](../logs/6_replay_req_equiv_ramulator_trace.log), [statistics](../results/clustered/replay_req_equiv/hbm2_stats.yaml) |


For scattered traffic, the DDR4/HBM2 time ratio falls from 1.554× in the
request-equivalent experiment to 1.235× in the byte-equivalent experiment.
For clustered traffic, it falls from 2.976× to 1.359×.

The apparent DDR4/HBM2 gap narrows after equalizing byte counts. DDR4's input
stays the same, while HBM2 receives a second transaction for each original
record. This demonstrates why the request-equivalent ratios alone are not an
equal-payload performance comparison. Neither ratio is application speedup.

## Byte-equivalent Trace Replay

| Pattern | Model | Logical Bytes (B) | Requests | Controller Cycles | Modeled Time (ms) |
|---|---|---:|---:|---:|---:|
| Scattered | DDR4 | 30,913,152 | 483,018 | 2,507,545 | 2.088785 |
| Scattered | HBM2 | 30,913,152 | 966,036 | 1,691,297 | 1.691297 |
| Clustered | DDR4 | 4,590,720 | 71,730 | 382,715 | 0.318802 |
| Clustered | HBM2 | 4,590,720 | 143,460 | 234,582 | 0.234582 |

With equal logical byte counts, HBM2 still finishes in less modeled time in
both cases. DDR4 takes 1.235× the HBM2 replay time for scattered traffic and
1.359× for clustered traffic. HBM2 processes twice as many requests to represent
the same bytes, so these ratios compare equal payloads rather than equal
transaction counts.

| Pattern | Model | Row-buffer Hit Rate | Average Read Latency (ns) |
|---|---|---:|---:|
| Scattered | DDR4 | 25.36% | 166.235 |
| Scattered | HBM2 | 55.32% | 78.933 |
| Clustered | DDR4 | 96.77% | 163.211 |
| Clustered | HBM2 | 95.83% | 70.179 |

Both models have much higher row-buffer hit rates for clustered traffic.
HBM2 has a higher hit rate for scattered traffic, while DDR4's clustered hit
rate is slightly higher than HBM2's. HBM2 nevertheless has lower average read
latency than DDR4 for both patterns; hit rate
alone does not explain replay time. Scheduling, model timing, and transaction
splitting also affect the comparison.

Row-buffer hit rate is `hits / (hits + misses + conflicts)`. Average read latency
is converted from each controller's cycles to nanoseconds using
`latency_cycles × tCK(ps) / 1000`. These are per-transaction averages: two HBM2
transactions represent each original 64-byte request, so the HBM2 value is not
the completion latency of that entire original request.

| Case | DDR4 Log | HBM2 Log | Audited Results |
|---|---|---|---|
| Scattered | [log](../logs/7_replay_byte_equiv_ramulator_trace.log) | [log](../logs/7_replay_byte_equiv_ramulator_trace.log) | [verification](../results/scattered/replay_byte_equiv/verification.json) |
| Clustered | [log](../logs/7_replay_byte_equiv_ramulator_trace.log) | [log](../logs/7_replay_byte_equiv_ramulator_trace.log) | [verification](../results/clustered/replay_byte_equiv/verification.json) |

The [payload summary](../results/payload_equivalent_summary.json) collects the
statistics used in both tables. Raw controller statistics are retained under
[scattered/replay_byte_equiv](../results/scattered/replay_byte_equiv/) and
[clustered/replay_byte_equiv](../results/clustered/replay_byte_equiv/).


| Pattern | HBM2 Replay-Time Reduction Relative to DDR4 | Equal Logical Payload |
|---|---:|---:|
| Scattered | 19.03% | 30,913,152 B |
| Clustered | 26.42% | 4,590,720 B |

These percentages use DDR4 time as the denominator. They express the same
comparison as the DDR4/HBM2 ratios, but as reductions in standalone replay time.
HBM2's transaction splitting changes queue occupancy and scheduling opportunities
as well as request count, so this is a comparison of the configured replay
systems rather than an isolated measurement of one DRAM property.

The row-buffer rates also need context. Adjacent HBM2 requests introduced by the
split can change the observed access stream and row reuse. The high clustered
hit rates therefore support a locality observation, but do not prove that hit
rate alone caused the timing differences. DDR4's clustered average read latency
changes only slightly even though its hit rate rises sharply, illustrating that
these statistics need to be considered together.

| Case | DDR4 Raw Statistics | HBM2 Raw Statistics | Input Transformation |
|---|---|---|---|
| Scattered | [statistics](../results/scattered/replay_byte_equiv/ddr4_stats.yaml) | [statistics](../results/scattered/replay_byte_equiv/hbm2_stats.yaml) | [input manifest](../results/scattered/replay_byte_equiv/input_manifest.json) |
| Clustered | [statistics](../results/clustered/replay_byte_equiv/ddr4_stats.yaml) | [statistics](../results/clustered/replay_byte_equiv/hbm2_stats.yaml) | [input manifest](../results/clustered/replay_byte_equiv/input_manifest.json) |

## Observations

| Assumption | Implication |
|---|---|
| Traffic is recorded after L2 during the gem5 ROI. | Counts reflect requests crossing that boundary, potentially including instruction traffic, rather than every source-level access. |
| Replay uses normalized injection and discards original gem5 timestamps. | Request spacing and queue pressure differ from the original CPU execution. |
| Both models consume traffic derived from gem5's DDR4 execution. | HBM2 latency does not feed back into CPU execution or change the captured request stream. |
| Each replay uses the configured single-controller memory model. | Results do not describe a complete HBM stack or an entire physical memory subsystem. |
| gem5 ROI time and standalone replay time come from separate simulations. | Replay ratios are not end-to-end SpMV speedups; the two times cannot be added to predict application runtime. |

These assumptions limit the findings to the recorded traffic and configured
models; predicting application performance with HBM2 would require its memory
responses to feed back into CPU execution.

| Comparison | Observation |
|---|---|
| Memory access locality | Clustered inputs reduce gem5 kernel time and exported post-L2 traffic in this setup. |
| Request-equivalent trace replay | HBM2 has lower replay time, but serves half the logical bytes because each model receives the same number of differently sized transactions. |
| Byte-equivalent trace replay | HBM2 has lower replay time for both patterns while serving the same logical byte volume as DDR4, using twice as many transactions. |

The byte-equivalent replay provides the main DDR4/HBM2 comparison because both
models serve the same logical data volume. The request-equivalent results show
how unequal payloads can widen the apparent timing gap.

