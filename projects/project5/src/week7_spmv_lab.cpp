// Week 7: CSR SpMV accelerator-oriented analytical lab (C++17).
//
// Build: g++ -std=c++17 -O2 -Wall -Wextra -pedantic week7_spmv_lab.cpp -o week7_spmv_lab
// Run:   ./week7_spmv_lab --mode baseline
//        ./week7_spmv_lab --mode sweep
//
// The performance model produces OPTIMISTIC analytical bounds, not measured FPGA
// performance. It excludes row-pointer/output traffic, transfers, queueing,
// reduction hazards, memory-bank conflicts, and protocol overhead.

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using Ints = std::vector<int>;

const Ints ROW_PTR{0, 2, 3, 5, 6};
const Ints COL_IDX{0, 3, 1, 0, 4, 2};
const Ints VALUES{2, 1, 3, 4, -1, 5};
const Ints X{1, 2, 3, 4, 5};
const Ints EXPECTED{6, 6, -1, 15};

void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

void validate_csr(const Ints& row_ptr, const Ints& col_idx,
                  const Ints& values, const Ints& x) {
    require(!row_ptr.empty(), "CSR row_ptr must not be empty");
    require(values.size() == col_idx.size(), "values/col_idx size mismatch");
    require(row_ptr.front() == 0, "CSR row_ptr must start at zero");
    require(row_ptr.back() == static_cast<int>(values.size()),
            "CSR row_ptr final offset must equal nnz");
    for (size_t i = 1; i < row_ptr.size(); ++i)
        require(row_ptr[i - 1] <= row_ptr[i], "CSR row_ptr must be nondecreasing");
    for (int col : col_idx)
        require(col >= 0 && col < static_cast<int>(x.size()),
                "CSR column index out of bounds");
}

Ints csr_spmv(const Ints& row_ptr, const Ints& col_idx,
              const Ints& values, const Ints& x) {
    validate_csr(row_ptr, col_idx, values, x);
    Ints y(row_ptr.size() - 1, 0);
    for (size_t row = 0; row < y.size(); ++row)
        for (int k = row_ptr[row]; k < row_ptr[row + 1]; ++k)
            y[row] += values[k] * x[col_idx[k]];
    return y;
}

Ints dense_oracle(const Ints& row_ptr, const Ints& col_idx,
                  const Ints& values, const Ints& x) {
    validate_csr(row_ptr, col_idx, values, x);
    std::vector<Ints> a(row_ptr.size() - 1, Ints(x.size(), 0));
    for (size_t row = 0; row < a.size(); ++row)
        for (int k = row_ptr[row]; k < row_ptr[row + 1]; ++k)
            a[row][col_idx[k]] += values[k];
    Ints y(a.size(), 0);
    for (size_t row = 0; row < a.size(); ++row)
        for (size_t col = 0; col < x.size(); ++col)
            y[row] += a[row][col] * x[col];
    return y;
}

std::pair<int, int> lru_miss_count(const Ints& stream, size_t capacity) {
    // Fully associative LRU cache, in logical x elements (not real cache lines).
    std::list<int> lru; // most recently used entry at front
    int hits = 0, misses = 0;
    for (int index : stream) {
        auto it = std::find(lru.begin(), lru.end(), index);
        if (it != lru.end()) {
            ++hits;
            lru.splice(lru.begin(), lru, it);
        } else {
            ++misses;
            if (capacity != 0) {
                if (lru.size() == capacity) lru.pop_back();
                lru.push_front(index);
            }
        }
    }
    return {hits, misses};
}

void print_vec(const Ints& v) {
    std::cout << '[';
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << ']';
}

void baseline() {
    const Ints actual = csr_spmv(ROW_PTR, COL_IDX, VALUES, X);
    const Ints reference = dense_oracle(ROW_PTR, COL_IDX, VALUES, X);
    require(actual == reference && actual == EXPECTED, "ORACLE FAIL: incorrect SpMV");

    Ints lengths;
    std::map<int, int> histogram;
    for (size_t row = 0; row + 1 < ROW_PTR.size(); ++row) {
        int len = ROW_PTR[row + 1] - ROW_PTR[row];
        lengths.push_back(len);
        ++histogram[len];
    }

    std::cout << "ORACLE = PASS; y = ";
    print_vec(actual);
    std::cout << '\n';
    std::cout << "nnz = " << COL_IDX.size() << " row_lengths = ";
    print_vec(lengths);
    std::cout << " unique_x = " << std::set<int>(COL_IDX.begin(), COL_IDX.end()).size()
              << " total_gathers = " << COL_IDX.size() << '\n';
    std::cout << "row_length_histogram = {";

    bool first = true;
    for (const auto& [length, count] : histogram) {
        if (!first) std::cout << ", ";
        std::cout << length << ": " << count;
        first = false;
    }
    std::cout << "}\n";

    for (size_t capacity : {0u, 2u, 4u, 8u}) {
        auto [hits, misses] = lru_miss_count(COL_IDX, capacity);
        std::cout << "x_cache_entries=" << std::setw(2) << capacity
                  << "  hits=" << std::setw(2) << hits
                  << "  misses=" << std::setw(2) << misses
                  << "  miss_fraction=" << std::fixed << std::setprecision(3)
                  << static_cast<double>(misses) / COL_IDX.size() << '\n';
    }
}

struct ModelResult {
    double bytes_per_nnz, issue_gnnz_s, memory_gnnz_s, bound_gnnz_s;
    std::string limit;
};

ModelResult model(int lanes, double mhz, double bandwidth_gb_s, double miss_fraction) {
    // FP32 matrix value (4 B) + int32 column index (4 B) per nonzero;
    // average FP32 x fetch: 4 B * modeled miss fraction.
    require(lanes > 0 && mhz > 0 && bandwidth_gb_s > 0 &&
            miss_fraction >= 0 && miss_fraction <= 1, "invalid model parameters");
    double bytes = 8.0 + 4.0 * miss_fraction;
    double issue = lanes * mhz / 1000.0; // Gnonzeros/s; 1 nnz/cycle/lane
    double memory = bandwidth_gb_s / bytes;
    double rate = std::min(issue, memory);
    std::string limit = "balanced";
    if (issue < memory) limit = "issue";
    if (issue > memory) limit = "bandwidth";
    return {bytes, issue, memory, rate, limit};
}

void sweep() {
    std::cout << "MODEL: optimistic upper bounds, not measured FPGA throughput\n";
    std::cout << "Lanes MHz BW_GB/s x_miss bytes/nnz issue_Gnnz/s memory_Gnnz/s "
                 "bound_Gnnz/s bound_GFLOP/s limit\n";
    std::cout << std::fixed;

    for (double miss : {1.0, 0.5, 0.0})
        for (double bw : {2.0, 6.0, 12.0})
            for (int lanes : {1, 2, 4, 8}) {
                auto r = model(lanes, 200.0, bw, miss);
                std::cout << std::setw(5) << lanes << ' '
                          << std::setw(3) << 200 << ' '
                          << std::setw(7) << std::setprecision(1) << bw << ' '
                          << std::setw(6) << std::setprecision(2) << miss << ' '
                          << std::setw(8) << std::setprecision(2) << r.bytes_per_nnz << ' '
                          << std::setw(12) << std::setprecision(3) << r.issue_gnnz_s << ' '
                          << std::setw(13) << r.memory_gnnz_s << ' '
                          << std::setw(13) << r.bound_gnnz_s << ' '
                          << std::setw(13) << 2.0 * r.bound_gnnz_s << ' '
                          << r.limit << '\n';
            }
    std::cout << "\nSame nonzero count but different locality (valid x indices):\n";

    const std::map<std::string, Ints> patterns{
        {"clustered", {0, 1, 0, 1, 0, 1, 0, 1}},
        {"scattered", {0, 1, 2, 3, 4, 0, 1, 2}}
    };
    for (const auto& [name, pattern] : patterns) {
        auto [hits, misses] = lru_miss_count(pattern, 2);
        std::cout << "pattern=" << std::left << std::setw(10) << name << std::right
                  << " cache=2 hits=" << hits << " misses=" << misses
                  << " miss_fraction=" << std::setprecision(3)
                  << static_cast<double>(misses) / pattern.size() << '\n';
    }
    std::cout << "NOTE: patterns are synthetic gather streams, not equivalent matrices.\n";
}

int main(int argc, char** argv) {
    try {
        std::string mode = "baseline";

        if (argc == 3 && std::string(argv[1]) == "--mode") mode = argv[2];
        else if (argc != 1) {
            std::cerr << "Usage: " << argv[0] << " [--mode baseline|sweep]\n";
            return 2;
        }

        if (mode == "baseline") baseline();
        else if (mode == "sweep") sweep();
        else {
            std::cerr << "Unknown mode: " << mode << "\n";
            return 2;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
