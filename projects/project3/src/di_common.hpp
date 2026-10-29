#ifndef DI_COMMON_HPP
#define DI_COMMON_HPP

// Shared argument validation, layout permutation, and reproducible input data.
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

// Parse a nonzero dimension/count and reject trailing text or size_t overflow.
inline std::size_t positive_arg(const std::string& s, const char* field) {
    std::size_t used = 0;
    unsigned long long n = 0;
    try { n = std::stoull(s, &used); }
    catch (...) { throw std::runtime_error(std::string("Invalid ") + field); }
    if (used != s.size() || n == 0 || n > std::numeric_limits<std::size_t>::max())
        throw std::runtime_error(std::string("Invalid ") + field);
    return static_cast<std::size_t>(n);
}

// A positive power of two has exactly one set bit.
inline bool power_of_two(std::size_t n) { return n && !(n & (n - 1)); }

// Requires n to be a power of two. Apply the same mapping to column indices
// and feature rows to change memory locality while preserving A*X.
// Invertible on [0,2^b): right-XOR-shifts and multiplication by odd numbers
// are bijective modulo 2^b. Unlike the original affine stride, this mapping
// scrambles adjacent logical column IDs nonlinearly; not a true random sample.
inline std::size_t scrambled_id(std::size_t id, std::size_t n) {
    const std::uint64_t mask = static_cast<std::uint64_t>(n - 1);

    // Derive mixing shifts from the number of address bits in this domain.
    unsigned bits = 0;
    for (std::size_t t = n; t > 1; t >>= 1) ++bits;
    const unsigned shift_a = std::max(1u, bits / 2u);
    const unsigned shift_b = std::max(1u, bits / 3u);

    // Mask after multiplication to keep every intermediate in the domain.
    std::uint64_t x = static_cast<std::uint64_t>(id) & mask;
    x ^= x >> shift_a;
    x = (x * UINT64_C(0xbf58476d1ce4e5b9)) & mask;
    x ^= x >> shift_b;
    x = (x * UINT64_C(0x94d049bb133111eb)) & mask;
    x ^= x >> shift_a;
    return static_cast<std::size_t>(x & mask);
}

// =======================================================================================================
//   deterministic_* functions generate reproducible input values instead of a random-number generator.
// =======================================================================================================

// Scalar values (1 + logical % 97) / 16, repeating every 97 IDs.
// Unused by the current SpMM benchmark.
inline double deterministic_x(std::size_t logical) {
    return static_cast<double>(1 + (logical % 97)) / 16.0;
}

// X[c,f] = (1 + (7*c + 11*f) % 103) / 32, an exact binary fraction.
// Logical column IDs preserve feature values across local/permuted layouts.
inline double deterministic_feature(std::size_t logical_col, std::size_t feature) {
    return static_cast<double>(1 + ((logical_col * 7 + feature * 11) % 103)) / 32.0;
}

// Edge weights cycle through 1/8, 2/8, ..., 7/8 within every sparse row.
inline double deterministic_weight(std::size_t nonzero_within_row) {
    return static_cast<double>(1 + (nonzero_within_row % 7)) / 8.0;
}

#endif
