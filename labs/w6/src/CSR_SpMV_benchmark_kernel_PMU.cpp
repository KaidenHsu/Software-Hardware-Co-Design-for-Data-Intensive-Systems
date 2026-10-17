// Week 6 profiling benchmark: CSR SpMV with two semantics-equivalent
// address layouts.
//
// C++17, standard library only.
// Compile: g++ -O3 -g -fno-omit-frame-pointer -std=c++17 ...
// Optional --pmu uses Linux perf_event_open for the timed SpMV loop.

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstring>

#if defined(__linux__)
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#endif

// Standard-library facilities used by setup, timing, validation, and output.
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

#ifndef NCOLS_MULTIPLIER
#define NCOLS_MULTIPLIER 4
#endif

static std::size_t as_positive(const std::string& x, const char* name) {
    // Parse a command-line dimension and reject zero, trailing characters,
    // overflow, and other values that cannot describe a useful benchmark.
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
    // Bijective for power-of-two n because the multiplier is odd. Applying
    // this mapping changes physical addresses while preserving logical data.
    return (static_cast<std::uint64_t>(idx) * 2654435761ULL + 17ULL) & (n - 1);
}

#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
// Keep the kernel as a distinct call so perf can attribute samples to the
// measured SpMV operation.
static void csr_spmv(const std::vector<std::size_t>& rp,
                     const std::vector<std::uint32_t>& ci,
                     const std::vector<double>& val,
                     const std::vector<double>& x,
                     std::vector<double>& y) {
    // CSR stores each row's nonzeros in one contiguous range:
    // [rp[r], rp[r + 1]). The kernel multiplies those values by the
    // corresponding input entries and writes one output per row.
    for (std::size_t r = 0; r + 1 < rp.size(); ++r) {
        double s = 0.0;

        for (std::size_t k = rp[r]; k < rp[r + 1]; ++k)
            s += val[k] * x[ci[k]];

        y[r] = s;
    }
}

// One hardware-PMU group for the current thread.
//
// Counters are opened after setup and warm-up, enabled only around the timed
// loop, and read before correctness verification. This keeps initialization,
// allocation, and validation outside the PMU measurement.
//
// The implementation is Linux-specific. On other platforms, --pmu reports
// that the counters are unavailable instead of preventing normal timing.
class KernelPmu {
public:
    // requested_ records whether the caller asked for PMU measurements.
    explicit KernelPmu(bool requested) : requested_(requested) {}

    // The destructor closes all event file descriptors, including partially
    // opened groups after an error.
    ~KernelPmu() { close_fds(); }

    // A PMU group owns OS file descriptors. Copying would make two objects
    // appear to own the same descriptors, so both copy operations are disabled.
    KernelPmu(const KernelPmu&) = delete; // copy construction
    KernelPmu& operator=(const KernelPmu&) = delete; // copy assignment

    // Open the grouped hardware counters. The first event is the group leader;
    // the other events refer to that leader through group_fd.
    void prepare() {
        if (!requested_) return;

#if defined(__linux__)
        // Create one grouped counter set so cycles, instructions, and cache
        // misses cover the same interval. The first counter is the group
        // leader and controls enabling/disabling of all three events.
        constexpr std::uint64_t events[3] = {
            PERF_COUNT_HW_CPU_CYCLES,
            PERF_COUNT_HW_INSTRUCTIONS,
            PERF_COUNT_HW_CACHE_MISSES
        };
        constexpr const char* names[3] = {"cycles", "instructions", "cache-misses"};
        for (int i = 0; i < 3; ++i) {
            perf_event_attr attr{};

            attr.size = sizeof(attr);
            attr.type = PERF_TYPE_HARDWARE;
            attr.config = events[i];
            attr.disabled = (i == 0);          // the leader controls the group
            attr.exclude_kernel = 1;           // userspace only, like :u
            attr.exclude_hv = 1;
            attr.inherit = 0;                  // single-thread benchmark
            attr.read_format = PERF_FORMAT_GROUP |
                               PERF_FORMAT_TOTAL_TIME_ENABLED |
                               PERF_FORMAT_TOTAL_TIME_RUNNING;
            const int group_fd = (i == 0) ? -1 : fd_[0];
            const int new_fd = static_cast<int>(
                syscall(__NR_perf_event_open, &attr, 0, -1,
                        group_fd, PERF_FLAG_FD_CLOEXEC));

            if (new_fd < 0) {
                reason_ = std::string("opening ") + names[i] + ": " + std::strerror(errno);
                close_fds();
                return;
            }
            fd_[i] = new_fd;
        }
        ready_ = true;

#else
        reason_ = "Linux perf_event_open is unavailable on this operating system";
#endif
    }

    // Reset old counts and enable the entire group immediately before timing.
    void start() {
#if defined(__linux__)
        if (!ready_) return;
        // Reset and enable immediately before timing so setup and warm-up do
        // not contribute to the reported hardware-counter values.
        if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1 ||
            ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            reason_ = std::string("starting PMU counters: ") + std::strerror(errno);
            ready_ = false;
        }
#endif
    }

    // Stop the group and decode the group read format:
    // [event_count, time_enabled, time_running, counter_0, counter_1, ...].
    void stop() {
#if defined(__linux__)
        if (!ready_) return;
        if (ioctl(fd_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            reason_ = std::string("stopping PMU counters: ") + std::strerror(errno);
            ready_ = false;
            return;
        }

        // GROUP format: nr, time_enabled, time_running, then nr counter values.
        // A running time below the enabled time indicates multiplexing.
        std::array<std::uint64_t, 6> group{};
        const ssize_t count = read(fd_[0], group.data(), sizeof(group));
        if (count != static_cast<ssize_t>(sizeof(group)) || group[0] != 3) {
            reason_ = "PMU group read failed or returned an unexpected event count";
            ready_ = false;
            return;
        }
        time_enabled_ = group[1];
        time_running_ = group[2];
        for (int i = 0; i < 3; ++i)
            counts_[i] = group[i + 3];

        if (time_running_ == 0) {
            reason_ = "PMU events were not scheduled on hardware";
            ready_ = false;
            return;
        }
        valid_ = true;
#endif
    }

    // Print a machine-readable status line and derived IPC information.
    // Counts are not reported as valid if the group never ran.
    void report() const {
        if (!requested_) return;
        if (!valid_) {
            std::cout << "PMU_STATUS=UNAVAILABLE reason=" << reason_ << "\n";
            return;
        }
        // Scale interpretation is only reliable when the counters ran for
        // nearly the entire enabled interval; warn when the kernel multiplexed.
        const double running_fraction = static_cast<double>(time_running_) /
                                        static_cast<double>(time_enabled_);
        const double ipc = counts_[0] ? static_cast<double>(counts_[1]) /
                                       static_cast<double>(counts_[0]) : 0.0;
        std::cout << "PMU_STATUS=OK PMU_SCOPE=timed_spmv_loop_user_only"
                  << " cycles=" << counts_[0] << " instructions=" << counts_[1]
                  << " cache_misses=" << counts_[2] << " ipc=" << ipc
                  << " running_fraction=" << running_fraction << "\n";
        if (running_fraction < 0.99)
            std::cout << "PMU_WARNING=events_multiplexed; raw counts may undercount "
                         "(use fewer events or rerun)\n";
        std::cout << "PMU_NOTICE=cache_misses is CPU-dependent, not necessarily DRAM traffic\n";
    }

private:
    // Close every descriptor that was successfully opened. Checking each
    // descriptor makes cleanup safe after a partial prepare() failure.
    void close_fds() {
#if defined(__linux__)
        for (int& fd : fd_) {
            if (fd >= 0) {
                close(fd);
                fd = -1;
            }
        }
#endif
    }

    // requested_: caller requested PMU collection.
    // ready_: event descriptors opened and ready to start.
    // valid_: stop() successfully read a complete counter group.
    bool requested_ = false, ready_ = false, valid_ = false;

    std::string reason_ = "not initialized";
    std::array<std::uint64_t, 3> counts_{};
    std::uint64_t time_enabled_ = 0, time_running_ = 0;

#if defined(__linux__)
    int fd_[3] = {-1, -1, -1};
#endif
};

int main(int argc, char** argv) {
    try {
        // Defaults provide a repeatable, moderately sized benchmark while
        // allowing the matrix shape and address layout to be varied from the
        // command line.
        std::size_t rows = 65536, iters = 500, nnz_row = 8;
        std::string pattern = "local";
        bool request_pmu = false;
        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);

            if (arg == "--pmu") { request_pmu = true; continue; }
            if (i + 1 >= argc) throw std::runtime_error("Expected value after " + arg);
            if (arg == "--rows") rows = as_positive(argv[++i], "rows");
            else if (arg == "--iters") iters = as_positive(argv[++i], "iters");
            else if (arg == "--nnz-per-row") nnz_row = as_positive(argv[++i], "nnz-per-row");
            else if (arg == "--pattern") pattern = argv[++i];
            else throw std::runtime_error("Unknown argument: " + arg);
        }

        // Validate the shape before using it in the power-of-two permutation
        // and before allocating the benchmark arrays.
        if (pattern != "local" && pattern != "permuted")
            throw std::runtime_error("--pattern must be local or permuted");
        if ((rows & (rows - 1)) != 0 || rows < 4 || rows > (1U << 23))
            throw std::runtime_error("--rows must be a power of two in [4, 8388608]");
        if (nnz_row > 1024 || rows > std::numeric_limits<std::uint32_t>::max()/4ULL)
            throw std::runtime_error("Unsupported dimensions");
        const std::size_t ncols = rows * NCOLS_MULTIPLIER;
        if (rows > std::numeric_limits<std::size_t>::max()/nnz_row)
            throw std::runtime_error("Matrix too large");
        const std::size_t nnz = rows * nnz_row;



        // ==================== SETUP START ====================
        auto setup_start = std::chrono::steady_clock::now();

        // Build the matrix and the reference result before timing. The local
        // and permuted cases contain the same logical values; only the
        // physical positions used by x and col_idx differ.
        std::vector<std::size_t> row_ptr(rows + 1);
        std::vector<std::uint32_t> col_idx(nnz);
        std::vector<double> values(nnz), x(ncols), y(rows), expected(rows);

        // Place the logical input vector either contiguously or through the
        // permutation. The mathematical input remains the same in both cases.
        for (std::size_t i = 0; i < ncols; ++i) {
            std::size_t physical = (pattern == "local") ? i : permutation(i, ncols);
            x[physical] = static_cast<double>(1 + i % 97) / 16.0;
        }

        // Construct the CSR structure and an independent oracle for each row.
        for (std::size_t r = 0; r < rows; ++r) {
            row_ptr[r] = r * nnz_row;
            double expected_sum = 0.0;
            for (std::size_t j = 0; j < nnz_row; ++j) {
                const std::size_t k = r * nnz_row + j;
                const std::size_t logical = k % ncols;
                const std::size_t physical = (pattern == "local") ? logical : permutation(logical, ncols);
                col_idx[k] = static_cast<std::uint32_t>(physical);
                values[k] = static_cast<double>(1 + j % 7) / 8.0;
                // All inputs are exact binary fractions, so the oracle can be
                // compared directly with the kernel output.
                expected_sum += values[k] * (static_cast<double>(1 + logical % 97) / 16.0);
            }
            expected[r] = expected_sum;
        }
        row_ptr[rows] = nnz;

        const auto setup_end = std::chrono::steady_clock::now();
        // ===================== SETUP END =====================



        // Warm-up removes first-use effects and confirms that the generated
        // CSR representation agrees with the independently computed oracle.
        csr_spmv(row_ptr, col_idx, values, x, y);  // warm-up, outside timed region
        if (y != expected) throw std::runtime_error("FAIL: warm-up differs from oracle");

        KernelPmu pmu(request_pmu);



        // ==================== KERNEL START ===================
        // PMU setup occurs outside the timed region. start() resets and enables
        // the counters immediately before the repeated kernel calls.
        pmu.prepare();
        pmu.start();

        const auto start = std::chrono::steady_clock::now();

        // Only repeated kernel execution belongs in the performance interval.
        for (std::size_t i = 0; i < iters; ++i)
            csr_spmv(row_ptr, col_idx, values, x, y);

        const auto stop = std::chrono::steady_clock::now();

        pmu.stop();
        // ===================== KERNEL END ====================



        // Stop and read counters before performing post-run validation.
        // Validate the timed result as well, then derive throughput metrics
        // from the same interval used for the kernel timing.
        if (y != expected) throw std::runtime_error("FAIL: timed output differs from oracle");

        // A checksum makes output comparisons across runs straightforward.
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
        pmu.report();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
}
