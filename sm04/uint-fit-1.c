#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int get_left_1(uint32_t v) {
    int counter = 0;
    while (v ^ 0) {
        v >>= 1;
        ++counter;
    }
    return counter - 1;
}

int get_right_1(uint32_t v) {
    int counter = 0;
    while (!(v & 1)) {
        v >>= 1;
        ++counter;
    }
    return counter;
}

unsigned int FLOAT_SIGNIFICAND_BYTE_SIZE = 23U;

int is_uint_fit(uint32_t v) {
    if (v == 0U) {
        return 1;
    }
    return get_left_1(v) - get_right_1(v) <= FLOAT_SIGNIFICAND_BYTE_SIZE;
}

void test_get_left_1() {
    // Small.
    assert(get_left_1(1U) == 0);
    assert(get_left_1(2U) == 1);
    assert(get_left_1(3U) == 1);
    assert(get_left_1(4U) == 2);
    assert(get_left_1(5U) == 2);
    assert(get_left_1(6U) == 2);
    assert(get_left_1(7U) == 2);
    assert(get_left_1(8U) == 3);
    // 42 = 101010
    assert(get_left_1(42) == 5);
    // 2^31 - 1, 2^31
    assert(get_left_1(2147483647) == 30);
    assert(get_left_1(2147483648) == 31);
    // 2^32 - 2, 2^32 - 1
    assert(get_left_1(4294967294) == 31);
    assert(get_left_1(4294967295) == 31);
    fprintf(stderr, "get_left_1() -> OK\n");
}

void test_get_right_1() {
    // Small.
    assert(get_right_1(1U) == 0);
    assert(get_right_1(2U) == 1);
    assert(get_right_1(3U) == 0);
    assert(get_right_1(4U) == 2);
    assert(get_right_1(5U) == 0);
    assert(get_right_1(6U) == 1);
    assert(get_right_1(7U) == 0);
    assert(get_right_1(8U) == 3);
    // 42 = 101010
    assert(get_right_1(42) == 1);
    // 2^31 - 1, 2^31
    assert(get_right_1(2147483647) == 0);
    assert(get_right_1(2147483648) == 31);
    // 2^32 - 2, 2^32 - 1
    assert(get_right_1(4294967294) == 1);
    assert(get_right_1(4294967295) == 0);
    fprintf(stderr, "get_right_1() -> OK\n");
}

uint32_t convert(uint32_t v) {
    return (uint32_t)(float) v;
}

void test_is_uint_fit() {
    uint32_t two_in_20 = (1U << 20) + 1;
    uint32_t two_in_21 = (1U << 21) + 1;
    uint32_t two_in_22 = (1U << 22) + 1;
    uint32_t two_in_23 = (1U << 23) + 1;
    uint32_t two_in_24 = (1U << 24) + 1;
    uint32_t two_in_25 = (1U << 25) + 1;
    // Loop tests.
    for (int max_bit = 25; max_bit != 32; ++max_bit) {
        fprintf(stderr, "Max bit is the %dth one\n", max_bit);
        assert(is_uint_fit(two_in_20) == (two_in_20 == convert(two_in_20)));
        assert(is_uint_fit(two_in_21) == (two_in_21 == convert(two_in_21)));
        assert(is_uint_fit(two_in_22) == (two_in_22 == convert(two_in_22)));
        assert(is_uint_fit(two_in_23) == (two_in_23 == convert(two_in_23)));
        assert(is_uint_fit(two_in_24) == (two_in_24 == convert(two_in_24)));
        assert(is_uint_fit(two_in_25) == (two_in_25 == convert(two_in_25)));
        two_in_20 *= 2;
        two_in_21 *= 2;
        two_in_22 *= 2;
        two_in_23 *= 2;
        two_in_24 *= 2;
        two_in_25 *= 2;
    }
    // 2^31 + 2^9, + 2^8, + 2^7
    assert(is_uint_fit(2147483648 + 512) == 1);
    assert(is_uint_fit(2147483648 + 256) == 1);
    assert(is_uint_fit(2147483648 + 128) == 0);
    // 2^31, 2^31 + 1
    assert(is_uint_fit(2147483648) == 1);
    assert(is_uint_fit(2147483648 + 1) == 0);
    fprintf(stderr, "is_uint_fit() -> OK\n");
}

// no builtins
int main() {
    uint32_t v = 0;
    while (scanf("%u", &v) == 1) {
        printf("%d\n", is_uint_fit(v));
    }
}

