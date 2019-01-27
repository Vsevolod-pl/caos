#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { NUM_BITS = 32 };

int overflow(uint64_t a, int n) {
    a = a >> n;
    int whole_size = 0, size = 32;
    
    while (a != 0) {
        ++whole_size;
        a = a >> 1;
    }

    return size < whole_size + n;
}

uint64_t rounding(uint64_t a, int n) {
    uint64_t fractional = 1, round, zero = 0;
    fractional = fractional << n;
    fractional -= 1;
    round = a & fractional;
    fractional = fractional << 1;
    fractional += 1;

    if (!round) {
        return 0;
    }

    fractional = 1;
    fractional = fractional << (n-1);

    if (!(round & fractional)) {
        return 0;
    } else if ((round & fractional) != round) {
        return 1;
    }

    fractional = fractional << 1;
    return (a & fractional) != zero;
}

uint32_t reference(uint32_t a, uint32_t b, int n)
{
    uint64_t mul_result = (uint64_t)a * (uint64_t)b;
    
    if (n > 0) {
        mul_result = (mul_result >> n) + rounding(mul_result, n);
    }

    if (overflow(mul_result, n)) {
        uint32_t t = 0;
        t = ~t;
        return t;
    }

    return (uint32_t)(mul_result);
}

void check_for_overflow(uint64_t *number, int n) {
    uint32_t max_uint32 = ~0U;
    if (*number > max_uint32) {
        uint32_t uint32_max = ~0U;
        *number = uint32_max;
    }
}

void bankers_rounding(uint64_t *number, int n) {
    if (*number & (1ULL << (n - 1))) {
        // We have xxx.1.
        if (*number & ((1ULL << (n - 1)) - 1)) {
            // We have xxx.1yyyy1 -> xx(x+1)
            *number >>= n;
            ++(*number);
        } else {
            // Rounding to nearest even.
            *number >>= n;
            // 1.5 -> 2, 0.5 -> 1.
            if (*number & 1) {
                ++(*number);
            }
        }
    } else {
        // We have xxx.0 -> xxx
        *number >>= n;
    }
}

uint32_t fixed_mul(uint32_t a, uint32_t b, int n) {
    uint64_t first = a, second = b;
    uint64_t result = first * second;
    if (n != 0) {
        bankers_rounding(&result, n);
    }
    if (n != NUM_BITS) {
        check_for_overflow(&result, n);
    }
    return result;
}

int first_bit(uint64_t x)
{
    for (int i = 63; i >= 0; --i) {
        if ((1 & (x >> i)) != 0) {
            return i;
        }
    }
    return -1;
}

uint32_t fixed_mul2(uint32_t a, uint32_t b, int n)
{
    uint64_t c = (uint64_t) a, d = (uint64_t) b;
    uint64_t mult = c * d;
    uint32_t big = ~0u;
    if (c != 0 && d != 0 && (mult < c || mult < d)) {
        return big;
    }
    int bit = first_bit(mult);
    if (bit >= 32 + n) {
        return big;
    }
    uint32_t ans = (uint32_t) (mult >> n);
    uint32_t drop = (uint32_t) mult & (~0ul >> (32 - n));
    if (n == 0) {
        return ans;
    }
    if (drop == (1u << (n - 1))) {
        if (ans % 2 != 0) {
            ans += 1;
        }
    } else {
        if (drop > (1u << (n - 1))) {
            ans += 1;
        }
    }
    return ans;
}

int main() {
    uint32_t a, b, c;
    while (42) {
        a = rand() % 1000;
        b = rand() % 1000;
        c = rand() % 33;
        a = 383;
        b = 886;
        c = 6;
        printf("%u %u %u\n", a, b, c);
        printf("%x\n", fixed_mul(a, b, c));
        printf("%x\n", fixed_mul2(a, b, c));
        assert(fixed_mul(a, b, c) == fixed_mul2(a, b, c));
    }
}

