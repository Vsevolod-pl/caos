#include <stdint.h>

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t product = 0;
    if (b >= c) {
        b %= c;
    }
    while (a) {
        if (a & 1) {
            if (b >= c - product) {
                product -= c;
            }
            product += b;
        }
        a >>= 1;

        if (b >= c - b) {
            b += (b - c);
        } else {
            b += b;
        }
    }
    return product;
}

