#ifndef DI_COMMON_HPP
#define DI_COMMON_HPP
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

inline std::size_t positive_arg(const std::string& s, const char* field) {
    std::size_t used=0;
    unsigned long long n=0;
    try { n=std::stoull(s,&used); }
    catch(...) { throw std::runtime_error(std::string("Invalid ")+field); }
    if (used!=s.size() || n==0 || n>std::numeric_limits<std::size_t>::max())
        throw std::runtime_error(std::string("Invalid ")+field);
    return static_cast<std::size_t>(n);
}
inline bool power_of_two(std::size_t n) { return n && !(n&(n-1)); }

// Invertible on [0,2^b): right-XOR-shifts and multiplication by odd numbers
// are bijective modulo 2^b. Unlike the original affine stride, this mapping
// scrambles adjacent logical column IDs nonlinearly; not a true random sample.
inline std::size_t scrambled_id(std::size_t id, std::size_t n) {
    const std::uint64_t mask = static_cast<std::uint64_t>(n-1);
    unsigned bits=0;
    for (std::size_t t=n; t>1; t>>=1) ++bits;
    const unsigned shift_a=std::max(1u,bits/2u);
    const unsigned shift_b=std::max(1u,bits/3u);
    std::uint64_t x=static_cast<std::uint64_t>(id)&mask;
    x ^= x >> shift_a;
    x = (x * UINT64_C(0xbf58476d1ce4e5b9)) & mask;
    x ^= x >> shift_b;
    x = (x * UINT64_C(0x94d049bb133111eb)) & mask;
    x ^= x >> shift_a;
    return static_cast<std::size_t>(x & mask);
}
inline double deterministic_x(std::size_t logical) {
    return static_cast<double>(1 + (logical%97)) / 16.0;
}
inline double deterministic_feature(std::size_t logical_col, std::size_t feature) {
    return static_cast<double>(1 + ((logical_col*7+feature*11)%103)) / 32.0;
}
inline double deterministic_weight(std::size_t nonzero_within_row) {
    return static_cast<double>(1 + (nonzero_within_row%7)) / 8.0;
}
#endif
