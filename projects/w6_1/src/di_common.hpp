#ifndef DI_COMMON_HPP
#define DI_COMMON_HPP

// Shared parsing, validation, permutation, and deterministic-data helpers.

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>


// Parse a positive decimal command-line argument with overflow protection.
inline std::size_t positive_arg(const std::string& text, const char* field) {
    std::size_t used = 0;
    unsigned long long number = 0;

    try {
        number = std::stoull(text, &used);
    } catch (...) {
        throw std::runtime_error(std::string("Invalid ") + field);
    }

    if (used != text.size() || number == 0 ||
        number > std::numeric_limits<std::size_t>::max()) {
        throw std::runtime_error(std::string("Invalid ") + field);
    }

    return static_cast<std::size_t>(number);
}


// The benchmark uses powers of two so the permutation can mask its output.
inline bool power_of_two(std::size_t number) {
    return number && !(number & (number - 1));
}


// Apply invertible XOR shifts and odd multipliers modulo 2^b.
// This scrambles adjacent logical IDs without pretending to be random data.
inline std::size_t scrambled_id(std::size_t id, std::size_t number) {
    const std::uint64_t mask = static_cast<std::uint64_t>(number - 1);
    unsigned bits = 0;

    for (std::size_t remaining = number; remaining > 1; remaining >>= 1) {
        ++bits;
    }

    const unsigned first_shift = std::max(1u, bits / 2u);
    const unsigned second_shift = std::max(1u, bits / 3u);
    std::uint64_t value = static_cast<std::uint64_t>(id) & mask;

    value ^= value >> first_shift;
    value = (value * UINT64_C(0xbf58476d1ce4e5b9)) & mask;
    value ^= value >> second_shift;
    value = (value * UINT64_C(0x94d049bb133111eb)) & mask;
    value ^= value >> first_shift;

    return static_cast<std::size_t>(value & mask);
}


// Deterministic values make checksums stable across repeated benchmark runs.
inline double deterministic_x(std::size_t logical_column) {
    return static_cast<double>(1 + (logical_column % 97)) / 16.0;
}


// Deterministic feature data retained for assignment-side experiments.
inline double deterministic_feature(std::size_t logical_column,
                                    std::size_t feature) {
    return static_cast<double>(
               1 + ((logical_column * 7 + feature * 11) % 103)) /
           32.0;
}


// Give each nonzero position in a row a repeatable weight.
inline double deterministic_weight(std::size_t nonzero_within_row) {
    return static_cast<double>(1 + (nonzero_within_row % 7)) / 8.0;
}


#endif
