# Project 7.2 CSR SpMV: Load Balancing across Three CSR Partitioning Schemes

## 1. Introduction

In his [NVIDIA Research presentation on merge-based SpMV](NVDA-Merge-Based-Parallel-Sparse-Matrix-Vector-Multiplication-merrill.pdf), Duane Merrill examines why sparse matrix–vector multiplication can have widely different GPU runtimes for matrices of similar size. SpMV computes `y = Ax` using the stored nonzeros of `A`. When those nonzeros are concentrated in a few rows, workers assigned the same number of rows can end up doing very different amounts of arithmetic. Merrill presents merge-based partitioning as a way to distribute that work more evenly.

The [Week 11 case study](Week11_Case_Study.pdf) compares row-based partitioning, nonzero splitting, and merge-based partitioning by looking at what each scheme balances and what happens when a row spans multiple workers. It then applies those tradeoffs to a two-lane FPGA accelerator, where a single command per cycle and conflicts in banked memory can limit how much parallel work the lanes can sustain.

## 2. Performance Consistency

<p align="center">
  <img src="images/performance-consistency-slide-11.png" alt="Performance Consistency, slide 11" width="49%">
  <img src="images/performance-inconsistency-slide-14.png" alt="Performance (In)consistency" width="49%">
</p>

Across roughly 4,200 matrices on a K40 GPU, merge-based SpMV showed stronger runtime correlation with problem size than cuSPARSE (0.79 vs. 0.31) and weaker throughput correlation with row-length variation (−0.02 vs. −0.24). Uneven rows and irregular accesses to `x` can affect runtime (slides 14–16, 48).

<p>
  <img src="images/examples-slide-13.png" alt="Examples, second slide" width="49%">
  <img src="images/spmv-performance-landscape-slide-16.png" alt="SpMV Performance Landscape, second slide" width="49%">
</p>

## 3. Partitioning Schemes

The three schemes divide CSR SpMV work among parallel workers by rows, by nonzeros, or by counting both. The table compares how each scheme balances work and handles rows that span partitions (slides 6–10).

| Scheme | What each worker gets | Tradeoff |
| --- | --- | --- |
| Row-based | Roughly equal numbers of whole rows | Each row has one owner, but long rows can leave other workers idle. |
| Nonzero splitting | Roughly equal numbers of nonzeros | Balances multiply-adds, but workers can cross different numbers of row boundaries and need to combine split-row sums. |
| Merge-based | Equal-length segments of a path that counts nonzeros and row boundaries | Balances the combined work but requires a fixup for split rows. |

## 4. Merge-Based Partitioning

The algorithm balances the total number of nonzero and row-boundary steps assigned to each worker (slides 35–36 and 43–47).

| Step | How it works |
| --- | --- |
| 1. Define the merge path | Logically merge CSR row-end offsets with nonzero indices. A path step either advances to the next nonzero or crosses a row boundary. |
| 2. Find partition boundaries | Divide the path into as many nearly equal segments as there are workers. Each worker searches along a diagonal of the merge grid to find its starting position. |
| 3. Process each segment | For each nonzero, multiply its value by the corresponding entry of `x` and accumulate the product. At a row boundary, emit the accumulated sum and reset the accumulator. |
| 4. Combine split-row sums | If a row crosses a partition boundary, add the partial sums for that row to produce its final entry in `y`. |

## 5. Results

<p align="center">
  <img src="images/spmv-results-slide-48.png" alt="Slide 48 comparing cuSPARSE and merge-based SpMV runtimes and correlations on an NVIDIA K40" width="85%">
</p>

NVIDIA tested double-precision CSR SpMV on a K40 GPU across roughly 4,200 matrices. In slide 48, runtime correlated more strongly with problem size for merge-based SpMV (0.79) than for cuSPARSE (0.31), so matrix size was a better predictor of runtime in this benchmark.

Throughput had a weaker relationship with both row-length variation (−0.02 vs. −0.24) and row-length skew (−0.07 vs. −0.23). The correlations closer to zero indicate that throughput was less tied to how uneven the row lengths were. These coefficients describe how the measured quantities vary together. Use the plotted runtimes to compare speed for a given matrix.

## 6. FPGA Design Implications

- **Use a matrix profile to recommend a partitioning scheme.** Borrow the profile-and-select idea from recommendation systems. Subtract consecutive CSR row offsets to build a histogram of nonzeros per row in `A`. Recommend whole-row partitioning when row lengths are fairly uniform and consider merge-based partitioning when many rows are short or empty and a few are much longer. Use the histogram to choose a scheme and the original CSR offsets to place partition boundaries. The histogram captures the distribution of row lengths, while the row order and column indices determine where long rows cluster and which memory banks the accesses target.
- **Balance the work that costs cycles.** NVIDIA’s merge path counts both nonzeros and row boundaries. On the FPGA, multiply-adds, row transitions, and memory stalls can have different costs. The command input accepts at most one command per cycle, bank conflicts can delay operand reads or result writes, and the row-hazard scoreboard can stall updates to the same output row. These limits determine how much concurrency the two lanes can sustain.
- **Split rows when the idle-cycle savings justify the reduction.** Whole-row ownership simplifies accumulation and writeback. Sharing a long row can keep both lanes busy, but the accelerator must retain and combine the partial sums before writing the final output. The benefit depends on how much idle time the split eliminates and how many cycles it adds for partial-sum handling.

## 7. Conclusion

In NVIDIA’s GPU measurements, runtime tracked problem size more closely with merge-based partitioning, and throughput was less sensitive to variation in row length. Counting both nonzeros and row boundaries gives workers a more even share of the arithmetic and row-processing work. The tradeoff is extra work at partition boundaries, where partial sums from a split row must be combined before writing the final result.

For the FPGA, histogram-guided partitioning is a proposal to match the scheme to the matrix. Compare it against fixed whole-row and merge-based partitioning on matrices with uniform and skewed row lengths. Measure end-to-end cycles, lane utilization, and stalls from command supply, bank conflicts, and row hazards. Include histogram construction and scheme selection in the cycle count when they are on the execution path.
