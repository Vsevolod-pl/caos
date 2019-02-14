#include <stdint.h>
#include <stdio.h>

int get_left_1(uint64_t v) {
    int counter = 0;
    while (v ^ 0) {
        v >>= 1;
        ++counter;
    }
    return counter - 1;
}

int get_right_1(uint64_t v) {
    int counter = 0;
    while (!(v & 1)) {
        v >>= 1;
        ++counter;
    }
    return counter;
}

enum { DOUBLE_SIGNIFICAND_BYTE_SIZE = 52U };

int64_t MAX_INT64() {
    return ~0ULL >> 1;
}

int64_t MIN_INT64() {
    return ~MAX_INT64();
}

int is_double_presented(int64_t v) {
    if (v == 0U) {
        return 1;
    }
    if (v == MIN_INT64()) {
        return 1;
    }
    if (v < 0) {
        v *= -1;
    }
    return get_left_1(v) - get_right_1(v) <= DOUBLE_SIGNIFICAND_BYTE_SIZE;
}

int main() {
    int64_t n;
    while (scanf("%lld", &n) == 1) {
        printf("%d\n", is_double_presented(n));
    }

    return 0;
}

