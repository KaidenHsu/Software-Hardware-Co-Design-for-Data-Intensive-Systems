// SpMM GNN neighbor-aggregation benchmark: Y=A*X, CSR A and row-major dense X.
// Source files di_common.hpp and di_kernel_pmu.hpp required alongside this file.
#include "di_common.hpp"
#include "di_kernel_pmu.hpp"
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

// workload: Sparse Matrix Multiplication Y = AX, where sparse A is in CSR format
// CSR row r occupies [rp[r], rp[r+1]); ci[k] and val[k] identify an edge.
// Dense X and Y are row-major, with `features` consecutive doubles per row.
#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
static void csr_spmm(
    // sparse CSR matrix A
    // dimension = rp.size()-1  x  x.size()/features
    const std::vector<std::size_t>& rp, // row ptrs of sparse matrix A
    const std::vector<std::uint32_t>& ci, // col idx of sparse matrix A
    const std::vector<double>& val, // values of sparse matrix A

    // input matrix x
    // dimension = x.size()/features x features
    const std::vector<double>& x,
    // output matrix y
    // dimension = ( rp.size()-1 x features ) x features
    std::vector<double>& y,

    std::size_t features // #(values in each row of x)
) {

    // One output row per sparse row; rp has an extra end pointer.
    for (std::size_t r = 0; r + 1 < rp.size(); ++r) {
        // Each invocation overwrites Y rather than accumulating prior results.
        // Row-major storage: row r starts at flat offset r * features.
        double* out = &y[r * features];
        for (std::size_t f = 0; f < features; ++f) out[f] = 0;

        // CSR entries for row r occupy [rp[r], rp[r + 1]); zeros are skipped.
        for (std::size_t k = rp[r]; k < rp[r + 1]; ++k) {
            // ci[k] selects a row of X; val[k] is A[r, ci[k]].
            const double* in = &x[static_cast<std::size_t>(ci[k]) * features];
            const double weight = val[k];

            // Add weighted features: Y[r,f] += A[r,c] * X[c,f], c = ci[k].
            // Features within a row are contiguous even in permuted mode.
            for (std::size_t f = 0; f < features; ++f) out[f] += weight * in[f];
        }
    }
}

// A fixed 3x4 sparse matrix times a 4x2 feature matrix gives a 3x2 result.
// The explicit answer checks CSR traversal independently of generated inputs.
static void selftest() {
    // A (3 x 4) stored in CSR format
    //     [ 2   0   0   1 ]
    //     [ 0  -1   3   0 ]
    //     [ 4   0   0   0 ]
    //
    //                   row 0       row 1     row 2
    // val =       [ 2,  1,   |  -1,  3,  |  4 ]
    // ci  =       [ 0,  3,   |   1,  2,  |  0 ]
    // rp  =       [ 0, 2, 4, 5 ]
    const std::vector<std::size_t> rp{0, 2, 4, 5}; // row ptr
    const std::vector<std::uint32_t> ci{0, 3, 1, 2, 0}; // col idx
    const std::vector<double> v{2, 1, -1, 3, 4}; // weight

    // X (4 x 2), flattened row by row below:
    //     [ 1   2 ]
    //     [ 2   1 ]
    //     [ 3   0 ]
    //     [ 4  -1 ]
    const std::vector<double> x{1, 2, 2, 1, 3, 0, 4, -1};

    // Y (3 x 2)
    std::vector<double> y(6);

    csr_spmm(rp, ci, v, x, y, 2);

    // Expected Y = A * X (3 x 2), flattened row by row below:
    //     [ 6   3 ]
    //     [ 7  -1 ]
    //     [ 4   8 ]
    if (y != std::vector<double>{6, 3, 7, -1, 4, 8})
        throw std::runtime_error("SpMM independent CSR oracle mismatch");
    std::cout << "SELFTEST=PASS CSR_SPMM_ORACLE=PASS\n";
}

int main(int argc, char** argv) {
    try {
        // Default assignment workload; each output row has nnzrow edges.
        std::size_t rows = 32768, nnzrow = 8, iters = 100, features = 32;
        std::string pattern = "local";
        bool request_pmu = false, do_selftest = false;

        // Boolean switches take no value; the remaining options consume one.
        for (int a = 1; a < argc; ++a) {
            const std::string arg = argv[a];
            if (arg == "--pmu") { request_pmu = true; continue; }
            if (arg == "--selftest") { do_selftest = true; continue; }
            if (a + 1 >= argc) throw std::runtime_error("Missing value after " + arg);
            if (arg == "--rows") rows = positive_arg(argv[++a], "rows");
            else if (arg == "--nnz-per-row") nnzrow = positive_arg(argv[++a], "nnz-per-row");
            else if (arg == "--iters") iters = positive_arg(argv[++a], "iters");
            else if (arg == "--features") features = positive_arg(argv[++a], "features");
            else if (arg == "--pattern") pattern = argv[++a];
            else throw std::runtime_error("Unknown flag: " + arg);
        }

        if (do_selftest) { selftest(); return 0; }

        // Power-of-two rows make ncols a power of two for the bijective scramble.
        // Bound dimensions and check products before allocating the arrays.
        if (pattern != "local" && pattern != "permuted") throw std::runtime_error("Pattern must be local or permuted");
        if (!power_of_two(rows) || rows < 4 || rows > 262144) throw std::runtime_error("rows must be power of two, 4 to 262144");
        if (nnzrow > 1024 || features > 128 || rows > std::numeric_limits<std::uint32_t>::max() / 4)
            throw std::runtime_error("Dimensions exceed supported bounds");
        if (rows > std::numeric_limits<std::size_t>::max() / nnzrow || rows * 4 > std::numeric_limits<std::size_t>::max() / features)
            throw std::runtime_error("Size overflow");

        const auto ncols = rows * 4, nnz = rows * nnzrow;



        // =================== BEGIN CSR kernel setup ===================
        // Setup includes allocation, input generation, and oracle construction.
        // It is reported separately from repeated kernel execution.
        const auto t0 = std::chrono::steady_clock::now();

        // 1. Allocate arrays.
        
        // sparse matrix A (R x C) represented in the Comparessed Sparse Row (CSR) format
        std::vector<std::size_t> rp(rows + 1);
        std::vector<std::uint32_t> ci(nnz);
        std::vector<double> val(nnz);

        // x: dense input features (C x F)
        // y: dense output (R x F)
        // expected: R x F
        std::vector<double> x(ncols * features), y(rows * features), expected(rows * features);

        // 2. Fill the input feature table.
        // Logical feature values are identical in both layouts. Only their
        // physical row addresses change under the deterministic permutation.
        for (std::size_t logical = 0; logical < ncols; ++logical) {
            const auto physical = (pattern == "local")? logical : scrambled_id(logical, ncols);
            for (std::size_t f = 0; f < features; ++f)
                x[physical * features + f] = deterministic_feature(logical, f);
        }

        // Build a fixed number of edges per row. Map column indices with the
        // same permutation as X so the mathematical product remains unchanged.
        for (std::size_t r = 0; r < rows; ++r) {
            // 3. Build the sparse row, row by row.
            rp[r] = r * nnzrow;

            for (std::size_t j = 0; j < nnzrow; ++j) {
                const std::size_t k = r * nnzrow + j;
                const std::size_t logical = k % ncols; // logical is the original col idx w/o any permutation

                // assigns the col idx of the k-th stored array in sparse matrix A
                ci[k] = static_cast<std::uint32_t>(pattern == "local" ? logical : scrambled_id(logical, ncols));

                const double weight = deterministic_weight(j);
                val[k] = weight;

                // 4. Compute the oracle directly from logical IDs alongside setup
                for (std::size_t f = 0; f < features; ++f)
                    expected[r * features + f] += weight * deterministic_feature(logical, f);
            }
        }
        // 5. CSR's final pointer marks the end of the last row's edge range.
        rp[rows] = nnz;

        const auto t1 = std::chrono::steady_clock::now();
        // =================== END CSR kernel setup ===================



        // Run once before timing to warm memory and verify the generated layout.
        csr_spmm(rp, ci, val, x, y, features);
        if (y != expected) throw std::runtime_error("SpMM warm-up mismatch with logical oracle");

        // Optional per-thread hardware counters bracket the timed loop (and
        // its clock reads). Wall-clock timing covers only repeated kernel calls.
        KernelPmu counters(request_pmu, "timed_spmm_loop_user_only");



        // =================== BEGIN PMU-timed CSR kernel ===================
        counters.prepare(); counters.start();
        const auto start = std::chrono::steady_clock::now();

        for (std::size_t it = 0; it < iters; ++it)
            csr_spmm(rp, ci, val, x, y, features);

        const auto stop = std::chrono::steady_clock::now();
        counters.stop();
        // =================== END PMU-timed CSR kernel ===================



        // Validate the final output outside timing. These generated binary
        // fractions and fixed reduction order allow an exact equality check.
        if (y != expected) throw std::runtime_error("SpMM result differs from logical oracle");

        // The checksum summarizes Y for comparison across layouts; correctness
        // above uses every element, since equal checksums alone are insufficient.
        double checksum = 0;
        for (const double item : y) checksum += item;

        // Normalize runtime by iterations and edge-feature contributions.
        // feature_table_MiB is X storage size, not measured DRAM traffic.
        const double secs = std::chrono::duration<double>(stop - start).count();

        std::cout << std::fixed << std::setprecision(6)
                 << "CORRECT=PASS kernel=SpMM pattern=" << pattern << " rows=" << rows
                 << " ncols=" << ncols << " nnz=" << nnz << " features=" << features
                 << " iters=" << iters << " checksum=" << checksum << "\n"
                 << "setup_s=" << std::chrono::duration<double>(t1 - t0).count()
                 << " timed_kernel_s=" << secs << " ms_per_iter=" << secs * 1000.0 / iters
                 << " ns_per_edge_feature=" << secs * 1e9 / (static_cast<double>(nnz) * features * iters)
                 << " feature_table_MiB=" << 8.0 * ncols * features / 1048576.0 << "\n";

        counters.report();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 2;
    }
}
