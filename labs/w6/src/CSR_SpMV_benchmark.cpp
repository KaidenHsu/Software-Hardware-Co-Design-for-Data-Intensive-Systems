#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

static std::size_t as_positive(const std::string& x, const char* name) {
    std::size_t pos = 0;
    unsigned long long v = 0;
    try {
        v = std::stoull(x, &pos);
    }
    catch (...) { throw std::runtime_error(std::string("Invalid ") + name); }

    if (pos != x.size() || v == 0 || v > std::numeric_limits<std::size_t>::max())
        throw std::runtime_error(std::string("Invalid ") + name);

    return static_cast<std::size_t>(v);
}

static std::size_t permutation(std::size_t idx, std::size_t n) {
    return (static_cast<std::uint64_t>(idx) * 2654435761ULL + 17ULL) & (n - 1);
}

#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
static void csr_spmv(const std::vector<std::size_t>& rp,
                     const std::vector<std::uint32_t>& ci,
                     const std::vector<double>& val,
                     const std::vector<double>& x,
                     std::vector<double>& y) {
    for (std::size_t r = 0; r + 1 < rp.size(); ++r) {
        double s = 0.0;

        for (std::size_t k = rp[r]; k < rp[r + 1]; ++k)
            s += val[k] * x[ci[k]];

        y[r] = s;
    }
}

int main(int argc, char** argv) {
    try {
        std::size_t rows = 65536, iters = 500, nnz_row = 8;
        std::string pattern = "local";
        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);

            if (i + 1 >= argc) throw std::runtime_error("Expected value after " + arg);

            if (arg == "--rows") rows = as_positive(argv[++i], "rows");
            else if (arg == "--iters") iters = as_positive(argv[++i], "iters");
            else if (arg == "--nnz-per-row") nnz_row = as_positive(argv[++i], "nnz-per-row");
            else if (arg == "--pattern") pattern = argv[++i];
            else throw std::runtime_error("Unknown argument: " + arg);
        }

        if (pattern != "local" && pattern != "permuted")
            throw std::runtime_error("--pattern must be local or permuted");
        if ((rows & (rows - 1)) != 0 || rows < 4 || rows > (1U << 23))
            throw std::runtime_error("--rows must be a power of two in [4, 8388608]");
        if (nnz_row > 1024 || rows > std::numeric_limits<std::uint32_t>::max()/4ULL)
            throw std::runtime_error("Unsupported dimensions");
        const std::size_t ncols = rows * 4;
        if (rows > std::numeric_limits<std::size_t>::max()/nnz_row)
            throw std::runtime_error("Matrix too large");
        const std::size_t nnz = rows * nnz_row;



        // ==================== SETUP START ====================
        auto setup_start = std::chrono::steady_clock::now();
        std::vector<std::size_t> row_ptr(rows + 1);
        std::vector<std::uint32_t> col_idx(nnz);
        std::vector<double> values(nnz), x(ncols), y(rows), expected(rows);

        for (std::size_t i = 0; i < ncols; ++i) {
            std::size_t physical = (pattern == "local") ? i : permutation(i, ncols);
            x[physical] = static_cast<double>(1 + i % 97) / 16.0;
        }

        for (std::size_t r = 0; r < rows; ++r) {
            row_ptr[r] = r * nnz_row;
            double expected_sum = 0.0;
            for (std::size_t j = 0; j < nnz_row; ++j) {
                const std::size_t k = r * nnz_row + j;
                const std::size_t logical = k % ncols;
                const std::size_t physical = (pattern == "local") ? logical : permutation(logical, ncols);
                col_idx[k] = static_cast<std::uint32_t>(physical);
                values[k] = static_cast<double>(1 + j % 7) / 8.0;
                expected_sum += values[k] * (static_cast<double>(1 + logical % 97) / 16.0);
            }
            expected[r] = expected_sum;
        }
        row_ptr[rows] = nnz;
        const auto setup_end = std::chrono::steady_clock::now();
        // ===================== SETUP END =====================



        csr_spmv(row_ptr, col_idx, values, x, y);
        if (y != expected) throw std::runtime_error("FAIL: warm-up differs from oracle");



        // ==================== KERNEL START ===================
        const auto start = std::chrono::steady_clock::now();

        for (std::size_t i = 0; i < iters; ++i)
            csr_spmv(row_ptr, col_idx, values, x, y);

        const auto stop = std::chrono::steady_clock::now();
        // ===================== KERNEL END ====================



        if (y != expected) throw std::runtime_error("FAIL: timed output differs from oracle");

        double checksum = 0.0;
        for (double z : y) checksum += z;
        const auto seconds = std::chrono::duration<double>(stop - start).count();
        const auto setup_seconds = std::chrono::duration<double>(setup_end - setup_start).count();
        const double per_iter_ms = seconds * 1000.0 / static_cast<double>(iters);
        const double ns_per_nnz = seconds * 1e9 / (static_cast<double>(iters) * static_cast<double>(nnz));
        std::cout << std::fixed << std::setprecision(6)
                  << "CORRECT=PASS pattern=" << pattern
                  << " rows=" << rows << " ncols=" << ncols << " nnz=" << nnz
                  << " iters=" << iters << " checksum=" << checksum << "\n"
                  << "setup_s=" << setup_seconds << " timed_kernel_s=" << seconds
                  << " ms_per_iter=" << per_iter_ms << " ns_per_nnz=" << ns_per_nnz << "\n"
                  << "NOTICE: kernel_s excludes setup/verification, but perf stat of the whole "
                     "process includes them. Increase iters to amortize overhead.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
}
