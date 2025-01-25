#ifndef RANDOM_HPP
#define RANDOM_HPP 1

#ifndef KK2_RANDOM_GEN_HPP
#define KK2_RANDOM_GEN_HPP 1

#include <algorithm>
#include <cassert>
#include <numeric>
#include <unordered_set>
#include <vector>

#ifndef KK2_RANDOM_SEED_HPP
#define KK2_RANDOM_SEED_HPP 1

#include <chrono>

namespace kk2 {

namespace random {

using u64 = unsigned long long;

u64 non_deterministic_seed() {
    u64 seed = std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
                   .count();
    seed ^= reinterpret_cast<u64>(&seed);
    seed ^= seed << 5;
    seed ^= seed >> 41;
    seed ^= seed << 20;
    return seed;
}

// u64 deterministic_seed() {
//     return 5801799128519729247ull;
// }

u64 seed() {
    return non_deterministic_seed();
}

} // namespace random

} // namespace kk2

#endif // KK2_RANDOM_SEED_HPP

// #include "seed.hpp"

namespace kk2 {

namespace random {

using i64 = long long;
using u64 = unsigned long long;

u64 xorshift128plus(u64 &x, u64 &y) {
    u64 t = x;
    t ^= t << 23;
    t ^= t >> 17;
    t ^= y ^ (y >> 26);
    x = y;
    y = t;
    return x + y;
}

constexpr int iterations = 100;

void warm_up(u64 &x, u64 &y) {
    for (int i = 0; i < iterations; i++) xorshift128plus(x, y);
}

u64 rng() {
    static bool first = true;
    static u64 x = seed(), y = seed();
    if (first) {
        warm_up(x, y);
        first = false;
    }
    return xorshift128plus(x, y);
}

// [l, r)
i64 rng(i64 l, i64 r) {
    assert(l < r);
    return l + rng() % (r - l);
}

// [l, r)
template <class T> std::vector<T> random_vector(int n, T l, T r) {
    std::vector<T> res(n);
    for (int i = 0; i < n; i++) res[i] = rng(l, r);
    return res;
}

// [l, r)
std::vector<i64> distinct_rng(i64 l, i64 r, i64 n) {
    assert(l < r and n <= r - l);
    std::unordered_set<i64> st;
    for (i64 i = n; i; --i) {
        i64 m = rng(l, r + 1 - i);
        if (st.find(m) != st.end()) m = r - i;
        st.insert(m);
    }
    std::vector<i64> res(st.begin(), st.end());
    std::sort(res.begin(), res.end());
    return res;
}

template <class Iter> void shuffle(Iter first, Iter last) {
    if (first == last) return;
    int len = 1;
    for (auto it = first + 1; it != last; ++it) {
        len++;
        int j = rng(0, len);
        if (j != len - 1) std::iter_swap(first + j, it);
    }
}

template <class T> std::vector<T> perm(int n) {
    std::vector<T> res(n);
    std::iota(res.begin(), res.end(), T(0));
    shuffle(res.begin(), res.end());
    return res;
}

template <class T> std::vector<T> choices(int l, int r, int k) {
    assert(l < r and k <= r - l);
    std::vector<T> res(r - l);
    std::iota(res.begin(), res.end(), T(l));
    shuffle(res.begin(), res.end());
    res.resize(k);
    return res;
}

} // namespace random

} // namespace kk2

#endif // KK2_RANDOM_GEN_HPP
// #include <kk2/random/gen.hpp>


#endif // RANDOM_HPP
