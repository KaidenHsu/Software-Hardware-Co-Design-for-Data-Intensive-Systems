#ifndef DI_KERNEL_PMU_HPP
#define DI_KERNEL_PMU_HPP

// Optional Linux per-thread PMU support for the timed kernel loop.
// Generic cache-miss counts are CPU-dependent and not necessarily DRAM traffic.

#include <array>
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#if defined(__linux__)
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#endif


class KernelPmu {
public:
    explicit KernelPmu(bool requested, std::string scope)
        : requested_(requested), scope_(std::move(scope)) {}

    ~KernelPmu() {
        close_fds();
    }

    KernelPmu(const KernelPmu&) = delete;
    KernelPmu& operator=(const KernelPmu&) = delete;

    // Open a grouped set of user-mode hardware counters when requested.
    void prepare() {
        if (!requested_) {
            return;
        }

#if defined(__linux__)
        constexpr std::uint64_t events[3] = {
            PERF_COUNT_HW_CPU_CYCLES,
            PERF_COUNT_HW_INSTRUCTIONS,
            PERF_COUNT_HW_CACHE_MISSES,
        };
        constexpr const char* names[3] = {
            "cycles", "instructions", "cache-misses",
        };

        for (int index = 0; index < 3; ++index) {
            perf_event_attr attributes{};
            attributes.size = sizeof(attributes);
            attributes.type = PERF_TYPE_HARDWARE;
            attributes.config = events[index];
            attributes.disabled = index == 0;  // Leader controls the group.
            attributes.exclude_kernel = 1;    // Match userspace-only :u counts.
            attributes.exclude_hv = 1;
            attributes.inherit = 0;            // Benchmark is single-threaded.
            attributes.read_format = PERF_FORMAT_GROUP |
                                     PERF_FORMAT_TOTAL_TIME_ENABLED |
                                     PERF_FORMAT_TOTAL_TIME_RUNNING;

            const int group_fd = index == 0 ? -1 : fd_[0];
            const int new_fd = static_cast<int>(syscall(
                __NR_perf_event_open, &attributes, 0, -1, group_fd,
                PERF_FLAG_FD_CLOEXEC));

            if (new_fd < 0) {
                reason_ = std::string("opening ") + names[index] + ": " +
                          std::strerror(errno);
                close_fds();
                return;
            }

            fd_[index] = new_fd;
        }

        ready_ = true;
#else
        reason_ = "Linux perf_event_open is unavailable on this operating system";
#endif
    }

    // Reset and enable the counter group immediately before timing.
    void start() {
#if defined(__linux__)
        if (!ready_) {
            return;
        }

        if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1 ||
            ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            reason_ = std::string("starting PMU counters: ") +
                      std::strerror(errno);
            ready_ = false;
        }
#endif
    }

    // Stop the group and decode its aggregate values.
    void stop() {
#if defined(__linux__)
        if (!ready_) {
            return;
        }

        if (ioctl(fd_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            reason_ = std::string("stopping PMU counters: ") +
                      std::strerror(errno);
            ready_ = false;
            return;
        }

        // Group format: count, enabled time, running time, then three values.
        std::array<std::uint64_t, 6> group{};
        const ssize_t count = read(fd_[0], group.data(), sizeof(group));

        if (count != static_cast<ssize_t>(sizeof(group)) || group[0] != 3) {
            reason_ = "PMU group read failed or unexpected event count";
            ready_ = false;
            return;
        }

        time_enabled_ = group[1];
        time_running_ = group[2];

        for (int index = 0; index < 3; ++index) {
            counts_[index] = group[index + 3];
        }

        if (time_running_ == 0) {
            reason_ = "PMU events were not scheduled on hardware";
            ready_ = false;
            return;
        }

        valid_ = true;
#endif
    }

    // Print a stable status instead of making optional PMU failure fatal.
    void report() const {
        if (!requested_) {
            return;
        }

        if (!valid_) {
            std::cout << "PMU_STATUS=UNAVAILABLE reason=" << reason_ << "\n";
            return;
        }

        const double running_fraction =
            static_cast<double>(time_running_) /
            static_cast<double>(time_enabled_);
        const double ipc = counts_[0]
                               ? static_cast<double>(counts_[1]) /
                                     static_cast<double>(counts_[0])
                               : 0.0;

        std::cout << "PMU_STATUS=OK PMU_SCOPE=" << scope_
                  << " cycles=" << counts_[0]
                  << " instructions=" << counts_[1]
                  << " cache_misses=" << counts_[2]
                  << " ipc=" << ipc
                  << " running_fraction=" << running_fraction << "\n";

        if (running_fraction < 0.99) {
            std::cout << "PMU_WARNING=events_multiplexed; raw counts may undercount "
                         "(use fewer events or rerun)\n";
        }

        std::cout << "PMU_NOTICE=cache_misses is CPU-dependent, not necessarily "
                     "DRAM traffic\n";
    }

private:
    // Release all descriptors, including partially opened groups after an error.
    void close_fds() {
#if defined(__linux__)
        for (int& descriptor : fd_) {
            if (descriptor >= 0) {
                close(descriptor);
                descriptor = -1;
            }
        }
#endif
    }

    bool requested_ = false;
    bool ready_ = false;
    bool valid_ = false;
    std::string scope_;
    std::string reason_ = "not initialized";
    std::array<std::uint64_t, 3> counts_{};
    std::uint64_t time_enabled_ = 0;
    std::uint64_t time_running_ = 0;

#if defined(__linux__)
    int fd_[3] = {-1, -1, -1};
#endif
};


#endif
