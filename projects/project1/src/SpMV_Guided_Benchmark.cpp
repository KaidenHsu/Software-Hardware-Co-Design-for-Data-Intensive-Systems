// SpMV guided-project benchmark, C++17, with an optional Linux PMU report.
// Companion headers provide shared deterministic data and PMU handling.
// The program prints exact, reproducible checksums for comparing layouts.

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


// Timed kernel: Compressed Sparse Row - Sparse Matrix-Vector Multiplication
#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
static void csr_spmv(const std::vector<std::size_t>& row_ptr,
                     const std::vector<std::uint32_t>& column_index,
                     const std::vector<double>& values,
                     const std::vector<double>& x,
                     std::vector<double>& y) {
    for (std::size_t row = 0; row + 1 < row_ptr.size(); ++row) {
        double sum = 0;

        for (std::size_t k = row_ptr[row]; k < row_ptr[row + 1]; ++k) {
            sum += values[k] * x[column_index[k]];
        }

        y[row] = sum;
    }
}


// Exercise the arithmetic independently of the generated benchmark matrix.
static void selftest() {
    const std::vector<std::size_t> row_ptr{0, 2, 4, 5};
    const std::vector<std::uint32_t> column_index{0, 3, 1, 2, 0};
    const std::vector<double> values{2, 1, -1, 3, 4};
    const std::vector<double> x{1, 2, 3, 4};
    std::vector<double> y(3);

    csr_spmv(row_ptr, column_index, values, x, y);
    if (y != std::vector<double>{6, 7, 4}) {
        throw std::runtime_error("spmv oracle mismatch");
    }

    // Confirm that each supported permutation is bijective.
    for (std::size_t n = 16; n <= 65536; n *= 4) {
        std::vector<std::uint8_t> used(n, 0);

        for (std::size_t i = 0; i < n; ++i) {
            const auto physical = scrambled_id(i, n);

            if (physical >= n || used[physical]) {
                throw std::runtime_error("permutation not bijective");
            }

            used[physical] = 1;
        }
    }

    std::cout << "SELFTEST=PASS CSR_ORACLE=PASS SCRAMBLE_BIJECTION=PASS\n";
}


int main(int argc, char** argv) {
    try {
        // Defaults match the assignment's recommended measurement workload.
        std::size_t rows = 65536;
        std::size_t nnz_per_row = 8;
        std::size_t iterations = 500;
        std::string pattern = "local";
        bool pmu_requested = false;
        bool run_selftest = false;

        // Parse the small command-line interface used by the README commands.
        for (int argument = 1; argument < argc; ++argument) {
            const std::string option = argv[argument];

            if (option == "--pmu") { pmu_requested = true; continue; }
            if (option == "--selftest") { run_selftest = true; continue; }

            if (argument + 1 >= argc) { throw std::runtime_error("Missing argument to " + option); }

            if (option == "--rows") {
                rows = positive_arg(argv[++argument], "rows");
            } else if (option == "--nnz-per-row") {
                nnz_per_row = positive_arg(argv[++argument], "nnz-per-row");
            } else if (option == "--iters") {
                iterations = positive_arg(argv[++argument], "iters");
            } else if (option == "--pattern") {
                pattern = argv[++argument];
            } else {
                throw std::runtime_error("Unknown flag: " + option);
            }
        }

        if (run_selftest) { selftest(); return 0; }

        if (pattern != "local" && pattern != "permuted") {
            throw std::runtime_error("Pattern must be local or permuted");
        }

        if (!power_of_two(rows) || rows < 4 || rows > 2097152) {
            throw std::runtime_error(
                "rows must be a power of two between 4 and 2097152");
        }

        if (nnz_per_row > 1024 ||
            rows > std::numeric_limits<std::uint32_t>::max() / 4) {
            throw std::runtime_error("Unsupported matrix dimensions");
        }

        if (rows > std::numeric_limits<std::size_t>::max() / nnz_per_row) {
            throw std::runtime_error("NNZ overflow");
        }

        const std::size_t column_count = rows * 4;
        const std::size_t nonzero_count = rows * nnz_per_row;



        // ==================== SETUP START ====================
        const auto setup_start = std::chrono::steady_clock::now();

        std::vector<std::size_t> row_ptr(rows + 1);
        std::vector<std::uint32_t> column_index(nonzero_count);
        std::vector<double> values(nonzero_count);
        std::vector<double> x(column_count);
        std::vector<double> y(rows);
        std::vector<double> expected(rows);

        // Store x in either logical order or a bijective physical order.
        for (std::size_t logical = 0; logical < column_count; ++logical) {
            const auto physical = pattern == "local" ? logical : scrambled_id(logical, column_count);
            x[physical] = deterministic_x(logical);
        }

        // Generate a fixed-width CSR matrix and an independent expected result.
        for (std::size_t row = 0; row < rows; ++row) {
            row_ptr[row] = row * nnz_per_row;
            double reference = 0;

            for (std::size_t offset = 0; offset < nnz_per_row; ++offset) {
                const auto index = row * nnz_per_row + offset;
                const auto logical_column = index % column_count;
                const auto physical_column = pattern == "local" ? logical_column : scrambled_id(logical_column, column_count);

                column_index[index] = static_cast<std::uint32_t>(physical_column);
                values[index] = deterministic_weight(offset);
                reference += deterministic_weight(offset) * deterministic_x(logical_column);
            }

            expected[row] = reference;
        }

        row_ptr[rows] = nonzero_count;
        
        const auto setup_end = std::chrono::steady_clock::now();
        // ===================== SETUP END =====================



        // Check the generated matrix before collecting timing or PMU data.
        csr_spmv(row_ptr, column_index, values, x, y);
        if (y != expected) {
            throw std::runtime_error(
                "Warm-up differs from independent logical oracle");
        }



        KernelPmu counters(pmu_requested, "timed_spmv_loop_user_only");
        counters.prepare();



        // ==================== KERNEL START ===================
        counters.start();
        const auto kernel_start = std::chrono::steady_clock::now();

        for (std::size_t iteration = 0; iteration < iterations; ++iteration) {
            csr_spmv(row_ptr, column_index, values, x, y);
        }

        const auto kernel_end = std::chrono::steady_clock::now();
        counters.stop();
        // ===================== KERNEL END ====================



        if (y != expected) {
            throw std::runtime_error(
                "Final output differs from logical oracle");
        }

        double checksum = 0;
        for (const auto value : y) {
            checksum += value;
        }

        const double seconds = std::chrono::duration<double>(kernel_end - kernel_start).count();

        std::cout << std::fixed << std::setprecision(6)
                  << "CORRECT=PASS kernel=SpMV pattern=" << pattern
                  << " rows=" << rows << " ncols=" << column_count
                  << " nnz=" << nonzero_count << " iters=" << iterations
                  << " checksum=" << checksum << "\n"
                  << "setup_s="
                  << std::chrono::duration<double>(setup_end - setup_start).count()
                  << " timed_kernel_s=" << seconds
                  << " ms_per_iter="
                  << seconds * 1000.0 / static_cast<double>(iterations)
                  << " ns_per_nnz="
                  << seconds * 1e9 /
                         (static_cast<double>(nonzero_count) * iterations)
                  << " x_MiB=" << 8.0 * column_count / 1048576.0 << "\n";

        counters.report();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "ERROR: " << error.what() << "\n";
        return 2;
    }
}
