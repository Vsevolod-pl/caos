#include <assert.h>
#include <stdint.h>
#include <stdio.h>

typedef int8_t STYPE;
typedef uint8_t UTYPE;

int bitcount(STYPE value) {
    return 42;
}

void test_bitcount() {
    // Common tests.
    assert(bitcount(0) == 0);
    assert(bitcount(1) == 1);
    assert(bitcount(2) == 1);
    assert(bitcount(64) == 1);
    assert(bitcount(127) == 7);
    fprintf(stderr, "bitcount(): Common tests -> OK\n");

    // Test for specific types.
    UTYPE max_uint = ~((UTYPE)0);
    int shift;
    if (max_uint == (uint8_t)~((uint8_t)0)) {
        shift = 0;

        assert(bitcount(127) == 7 + shift);
        assert(bitcount(126) == 7 + shift - 1);
        assert(bitcount(-128) == 1);
        assert(bitcount(-127) == 2);

        fprintf(stderr, "bitcount(): Common tests for int%d_t -> OK\n", shift + 8);
    }
    if (max_uint == (uint16_t)~((uint16_t)0)) {
        shift = 8;

        assert(bitcount(32767) == 7 + shift);
        assert(bitcount(32766) == 7 + shift - 1);
        assert(bitcount(-32768) == 1);
        assert(bitcount(-32767) == 2);

        fprintf(stderr, "bitcount(): Common tests for int%d_t -> OK\n", shift + 8);
    }
    if (max_uint == (uint32_t)~((uint32_t)0)) {
        shift = 24;

        assert(bitcount(2147483647) == 7 + shift);
        assert(bitcount(2147483646) == 7 + shift - 1);
        assert(bitcount(-2147483648) == 1);
        assert(bitcount(-2147483647) == 2);

        fprintf(stderr, "bitcount(): Common tests for int%d_t -> OK\n", shift + 8);
    }
    if (max_uint == (uint64_t)~((uint64_t)0)) {
        shift = 56;

        assert(bitcount(9223372036854775807) == 7 + shift);
        assert(bitcount(9223372036854775806) == 7 + shift - 1);
        assert(bitcount(-9223372036854775808) == 1);
        assert(bitcount(-9223372036854775807) == 2);

        fprintf(stderr, "bitcount(): Common tests for int%d_t -> OK\n", shift + 8);
    }

    // Tests with shift.
    assert(bitcount(-1) == 8 + shift);
    assert(bitcount(-2) == 7 + shift);
    assert(bitcount(-3) == 7 + shift);
    assert(bitcount(-4) == 6 + shift);
    assert(bitcount(-127) == 2 + shift);
    assert(bitcount(-128) == 1 + shift);

    fprintf(stderr, "bitcount(): Tests with shift for int%d_t -> OK\n", shift + 8);
}

int main() {
    test_bitcount();
}

