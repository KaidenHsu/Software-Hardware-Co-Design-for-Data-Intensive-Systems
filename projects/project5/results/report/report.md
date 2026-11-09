# Week 8 experiment evidence

Status: COMPLETE.

## gem5 kernel execution (DDR4 baseline)

| Pattern | ROI ms | Post-L2 requests | Logical bytes |
|---|---:|---:|---:|
| scattered | 47.385717 | 483018 | 30913152 |
| clustered | 13.706270 | 71730 | 4590720 |

## Byte-equivalent standalone Ramulator replay

| Pattern | DRAM | Bytes | Requests | Cycles | tCK ps | Time ms | Row-hit % | Outstanding |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| scattered | ddr4 | 30913152 | 483018 | 2507545 | 833 | 2.088785 | 25.36 | 0 |
| scattered | hbm2 | 30913152 | 966036 | 1691297 | 1000 | 1.691297 | 55.32 | 0 |
| clustered | ddr4 | 4590720 | 71730 | 382715 | 833 | 0.318802 | 96.77 | 0 |
| clustered | hbm2 | 4590720 | 143460 | 234582 | 1000 | 0.234582 | 95.83 | 0 |

## Ratios and evidence

- gem5_time_scattered_to_clustered: 3.457229
- request_count_scattered_to_clustered: 6.733835
- scattered DDR4/HBM2 replay-time ratio: 1.235020
- clustered DDR4/HBM2 replay-time ratio: 1.359020
- check: validated
- baseline: validated
- replay: validated

## Interpretation limits

- HBM2 64B gem5 requests represented as 2x32B transactions; DDR4 retains 1x64B
- gem5 time and request sizes are not replayed; frontend issues requests at normalized 1-per-cycle
- single Ramulator modeled channel; not full DDR4 subsystem or complete HBM stack
- two different backends have different channel structures and address mapping
- gem5 ROI timestamp-filtered post-L2 stream includes possible non-data or outstanding traffic
- no gem5 closed-loop coupling; no physical FPGA or CPU memory speedup claimed

These tables are generated evidence, not the student's analytical conclusions.
Standalone HBM2 replay timing is not an end-to-end SpMV speedup.
