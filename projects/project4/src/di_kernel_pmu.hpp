#ifndef DI_KERNEL_PMU_HPP
#define DI_KERNEL_PMU_HPP
// Kernel-loop-only Linux PMU, two separate counter passes to avoid oversubscription.
// Generic L1/LLC/dTLB reads use PERF_TYPE_HW_CACHE; Emerald Rapids L2 uses Intel event 0x24/0x21.
#include <array>
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#if defined(__linux__)
    #include <linux/perf_event.h>
    #include <sys/ioctl.h>
    #include <sys/syscall.h>
    #include <unistd.h>

    #if defined(__x86_64__) || defined(__i386__)
        #include <cpuid.h>
    #endif
#endif



class KernelPmu {
public:
    enum class Mode { Core, Levels };
    // Store whether counters are requested, the measurement scope, and the selected event mode.
    KernelPmu(bool requested, std::string scope, Mode mode = Mode::Core)
        : requested_(requested), scope_(std::move(scope)), mode_(mode) {}
    // Close all opened PMU file descriptors when the object is destroyed.
    ~KernelPmu() { close_all(); }
    // Prevent copying because the object owns operating-system file descriptors.
    KernelPmu(const KernelPmu&) = delete;
    // Prevent assignment for the same file-descriptor ownership reason.
    KernelPmu& operator=(const KernelPmu&) = delete;

    // Open the hardware events required by the selected PMU mode.
    void prepare() {
        if (!requested_) return;
#if defined(__linux__)
        if (mode_ == Mode::Core) {
            add("cycles", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CPU_CYCLES);
            add("instructions", PERF_TYPE_HARDWARE, PERF_COUNT_HW_INSTRUCTIONS);
            add("cache_misses", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES);
        } else {
            add("l1d_load_misses", PERF_TYPE_HW_CACHE, hw_cache_miss(PERF_COUNT_HW_CACHE_L1D));

            // Counts true L2 demand data-read misses, not all L2 traffic or prefetch misses.
            if (emerald_rapids()) add("l2_demand_rd_misses", PERF_TYPE_RAW, 0x2124);
            else unavailable_.push_back("l2_demand_rd_misses:requires_Intel_Emerald_Rapids_model_207");

            add("llc_load_misses", PERF_TYPE_HW_CACHE, hw_cache_miss(PERF_COUNT_HW_CACHE_LL));
            add("dtlb_load_misses", PERF_TYPE_HW_CACHE, hw_cache_miss(PERF_COUNT_HW_CACHE_DTLB));
        }
        if (fds_.empty()) reason_ = "no supported permitted hardware events";
#else
        reason_ = "Linux perf_event_open unavailable";
#endif
    }

    // Reset and enable the PMU event group before the timed kernel loop.
    void start() {
#if defined(__linux__)
        if (fds_.empty()) return;
        if (ioctl(fds_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) != 0 ||
            ioctl(fds_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) != 0) {
            reason_ = std::string("enabling counters: ") + std::strerror(errno);
            return;
        }
        started_ = true;
#endif
    }

    // Disable the event group, read its counts, and calculate scheduling validity.
    void stop() {
#if defined(__linux__)
        if (!started_) return;
        started_ = false;
        // disables the whole group
        if (ioctl(fds_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) != 0) {
            reason_ = std::string("disabling counters: ") + std::strerror(errno);
            return;
        }

        // reads from fds_[0] into the group vector
        std::vector<std::uint64_t> group(3 + fds_.size(), 0);
        const ssize_t want = static_cast<ssize_t>(group.size() * sizeof(std::uint64_t));
        const ssize_t got = read(fds_[0], group.data(), static_cast<std::size_t>(want));
        if (got != want || group[0] != fds_.size()) {
            reason_ = "invalid PMU group read";
            return;
        }

        // saves timing information
        enabled_ = group[1];
        running_ = group[2];
        if (!running_ || !enabled_) {
            reason_ = "counter group was not scheduled";
            return;
        }

        // copies each event's value into counts_
        for (std::size_t i = 0; i < fds_.size(); ++i) counts_[i] = group[i + 3];
        valid_ = true;
#endif
    }

    // Print the mode-specific measurements, status, and counter scheduling information.
    void report() const {
        if (!requested_) return;
        const bool levels = mode_ == Mode::Levels;
        const std::string status = valid_ ? (unavailable_.empty() ? "OK" : "PARTIAL") : "UNAVAILABLE";
        std::cout << "PMU_STATUS=" << status
                  << " PMU_MODE=" << (levels ? "levels" : "core")
                  << " PMU_SCOPE=" << scope_;
        if (levels) {
            print("l1d_load_misses");
            print("l2_demand_rd_misses");
            print("llc_load_misses");
            print("dtlb_load_misses");
        } else {
            print("cycles");
            print("instructions");
            print("cache_misses");
            const long double c = numeric("cycles"), i = numeric("instructions");
            if (valid_ && c > 0 && i >= 0) std::cout << " ipc=" << std::setprecision(6)
                                                       << static_cast<double>(i / c);
            else std::cout << " ipc=N/A";
        }
        if (valid_) std::cout << " running_fraction=" << std::fixed << std::setprecision(6)
                              << static_cast<double>(running_) / static_cast<double>(enabled_);
        else std::cout << " running_fraction=N/A";
        std::cout << '\n';
        if (!valid_) std::cout << "PMU_REASON=" << token(reason_) << '\n';
        if (!unavailable_.empty()) {
            std::cout << "PMU_UNAVAILABLE_EVENTS=";
            for (std::size_t i = 0; i < unavailable_.size(); ++i)
                std::cout << (i ? ";" : "") << unavailable_[i];
            std::cout << '\n';
        }
        if (valid_ && static_cast<double>(running_) / static_cast<double>(enabled_) < 0.99)
            std::cout << "PMU_WARNING=multiplexed_raw_counts_are_not_comparable_without_scaling\n";
        if (levels)
            std::cout << "PMU_NOTICE=L1_LLC_dTLB_are_CPU_dependent_load_miss_events;_L2_is_true_demand_data_read_misses_only;_no_event_equals_DRAM_bytes\n";
        else std::cout << "PMU_NOTICE=cache_misses_is_CPU_dependent_not_DRAM_bytes\n";
    }



private:

#if defined(__linux__)
    // Encode a read-miss event for a Linux hardware-cache performance counter.
    static std::uint64_t hw_cache_miss(std::uint64_t cache) {
        return cache | (static_cast<std::uint64_t>(PERF_COUNT_HW_CACHE_OP_READ) << 8) |
               (static_cast<std::uint64_t>(PERF_COUNT_HW_CACHE_RESULT_MISS) << 16);
    }

    // Check CPUID vendor, family, and model before using the EMR-specific L2 event.
    static bool emerald_rapids() {
#if defined(__x86_64__) || defined(__i386__)
        unsigned int a=0,b=0,c=0,d=0;
        if (!__get_cpuid(0, &a, &b, &c, &d)) return false;
        if (b != 0x756e6547 || d != 0x49656e69 || c != 0x6c65746e) return false; // GenuineIntel
        if (!__get_cpuid(1, &a, &b, &c, &d)) return false;

        const unsigned int family = (a >> 8) & 0xf;
        const unsigned int model = ((a >> 4) & 0xf) | ((a >> 12) & 0xf0);
        return family == 6 && model == 0xcf; // Family 6, model 207
#else
        return false;
#endif
    }

    // Convert whitespace in kernel error messages into output-safe underscores.
    static std::string token(std::string v) {
        for (char &c : v) if (c == ' ' || c == '\t' || c == '\n') c = '_';
        return v;
    }

    // Configure and open one event, adding it to the shared PMU event group.
    void add(const char* name, std::uint32_t type, std::uint64_t config) {
        // perf_event_attr is a Linux kernel structure
        // used to describe a performance event
        perf_event_attr attr{};
        attr.size = sizeof(attr);
        attr.type = type;
        attr.config = config;
        attr.disabled = fds_.empty() ? 1U : 0U;
        attr.exclude_kernel = 1;
        attr.exclude_hv = 1;
        attr.inherit = 0;
        attr.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_TOTAL_TIME_ENABLED |
                           PERF_FORMAT_TOTAL_TIME_RUNNING;

        // perf_event_attr is passed to perf_event_open
        // returns a file descriptor on success and -1 on failure
        const int fd = static_cast<int>(syscall(__NR_perf_event_open, &attr, 0, -1,
                                               fds_.empty() ? -1 : fds_[0],
                                               PERF_FLAG_FD_CLOEXEC));
        if (fd < 0) {
            unavailable_.push_back(std::string(name) + ":" + token(std::strerror(errno)));
            return;
        }
        fds_.push_back(fd);
        names_.emplace_back(name);
        counts_.push_back(0);
    }
#else
    // Keep error-message formatting available on non-Linux builds.
    static std::string token(std::string v) { return v; }
#endif

    // Print one named counter value, or N/A when it was unavailable.
    void print(const char* name) const {
        std::cout << " " << name << "=";
        if (valid_)
            for (std::size_t k=0; k<names_.size(); ++k)
                if (names_[k] == name) { std::cout << counts_[k]; return; }
        std::cout << "N/A";
    }

    // Return one named counter as a number for derived metrics such as IPC.
    long double numeric(const char* name) const {
        if (valid_)
            for (std::size_t k=0; k<names_.size(); ++k)
                if (names_[k] == name) return static_cast<long double>(counts_[k]);
        return -1;
    }

    // Close every PMU file descriptor owned by this object.
    void close_all() {
#if defined(__linux__)
        for (const int fd : fds_) if (fd >= 0) close(fd);
        fds_.clear();
#endif
    }



    bool requested_ = false, started_ = false, valid_ = false;
    std::string scope_;
    Mode mode_;
    std::string reason_ = "not initialized";
    std::vector<std::string> names_, unavailable_;
    std::vector<std::uint64_t> counts_;
    std::uint64_t enabled_ = 0, running_ = 0;

#if defined(__linux__)
    // Store the Linux file descriptor for each successfully opened PMU event.
    //
    // The first descriptor, fds_[0], is the counter-group leader.  Each later
    // descriptor is opened with fds_[0] as its group leader, so all counters
    // belong to one group and cover the same timed kernel interval.  The
    // start() and stop() methods use fds_[0] to reset, enable, disable, and
    // read the complete group; the individual descriptors are retained here
    // so their order matches names_ and counts_.
    std::vector<int> fds_;
#endif
};
#endif
