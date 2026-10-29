#ifndef DI_KERNEL_PMU_HPP
#define DI_KERNEL_PMU_HPP

// Linux per-thread, user-mode kernel-loop PMU; generic cache_misses is CPU dependent.
// No sudo required when the host permits perf_event_open to this user.
#include <array>
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>

// Keep the benchmark buildable elsewhere; PMU requests then report unavailable.
#if defined(__linux__)
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#endif

// Usage: prepare() before timing, start()/stop() around the measured region,
// then report() outside timing. Counter failures leave the benchmark runnable.
class KernelPmu {
public:
    explicit KernelPmu(bool requested, std::string scope) : requested_(requested), scope_(std::move(scope)) {}
    ~KernelPmu() { close_fds(); }

    // File descriptors belong to this instance and must not be copied.
    KernelPmu(const KernelPmu&) = delete;
    KernelPmu& operator=(const KernelPmu&) = delete;

    // Open a group of three events for the calling thread on any CPU.
    void prepare() {
        if (!requested_) return;
#if defined(__linux__)
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

            // The cycles event leads the group; all events run together.
            // pid=0 selects this thread; cpu=-1 follows it across CPUs.
            const int group_fd = (i == 0) ? -1 : fd_[0];
            const int new_fd = static_cast<int>(
                syscall(__NR_perf_event_open, &attr, 0, -1,
                        group_fd, PERF_FLAG_FD_CLOEXEC));
            if (new_fd < 0) {
                // Release any events already opened if the group is incomplete.
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

    // Reset and enable the entire group through its leader descriptor.
    void start() {
#if defined(__linux__)
        if (!ready_) return;
        if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1 ||
            ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            reason_ = std::string("starting PMU counters: ") + std::strerror(errno);
            ready_ = false;
        }
#endif
    }

    // Disable counting before reading, so reporting work is excluded.
    void stop() {
#if defined(__linux__)
        if (!ready_) return;
        if (ioctl(fd_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            reason_ = std::string("stopping PMU counters: ") + std::strerror(errno);
            ready_ = false;
            return;
        }

        // GROUP format: nr, time_enabled, time_running, then nr counter values.
        std::array<std::uint64_t, 6> group{};
        const ssize_t count = read(fd_[0], group.data(), sizeof(group));
        if (count != static_cast<ssize_t>(sizeof(group)) || group[0] != 3) {
            reason_ = "PMU group read failed or returned an unexpected event count";
            ready_ = false;
            return;
        }

        // Enabled time is the requested interval; running time is the portion
        // during which hardware actually scheduled this event group.
        time_enabled_ = group[1];
        time_running_ = group[2];
        for (int i = 0; i < 3; ++i) counts_[i] = group[i + 3];
        if (time_running_ == 0) {
            reason_ = "PMU events were not scheduled on hardware";
            ready_ = false;
            return;
        }
        valid_ = true;
#endif
    }

    // Counts are raw (not scaled for multiplexing).
    void report() const {
        if (!requested_) return;
        if (!valid_) {
            std::cout << "PMU_STATUS=UNAVAILABLE reason=" << reason_ << "\n";
            return;
        }

        const double running_fraction = static_cast<double>(time_running_) /
                                        static_cast<double>(time_enabled_);
        const double ipc = counts_[0] ? static_cast<double>(counts_[1]) /
                                       static_cast<double>(counts_[0]) : 0.0;
        std::cout << "PMU_STATUS=OK PMU_SCOPE=" << scope_
                  << " cycles=" << counts_[0] << " instructions=" << counts_[1]
                  << " cache_misses=" << counts_[2] << " ipc=" << ipc
                  << " running_fraction=" << running_fraction << "\n";
        if (running_fraction < 0.99)
            std::cout << "PMU_WARNING=events_multiplexed; raw counts may undercount "
                         "(use fewer events or rerun)\n";
        std::cout << "PMU_NOTICE=cache_misses is CPU-dependent, not necessarily DRAM traffic\n";
    }

private:
    // Also handles partially opened groups during prepare() failure.
    void close_fds() {
#if defined(__linux__)
        for (int& fd : fd_) {
            if (fd >= 0) { close(fd); fd = -1; }
        }
#endif
    }

    // requested_: user opted in; ready_: group usable; valid_: read succeeded.
    bool requested_ = false, ready_ = false, valid_ = false;
    std::string scope_;
    std::string reason_ = "not initialized";

    // Counter order matches prepare(): cycles, instructions, cache misses.
    std::array<std::uint64_t, 3> counts_{};
    std::uint64_t time_enabled_ = 0, time_running_ = 0;
#if defined(__linux__)
    // -1 marks an unopened or closed descriptor; fd_[0] is the group leader.
    int fd_[3] = {-1, -1, -1};
#endif
};

#endif
