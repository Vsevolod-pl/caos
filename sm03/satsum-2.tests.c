#include <assert.h>
#include <stdint.h>

int32_t MAX_INT() {
    return ~0U >> 1;
}

int32_t MIN_INT() {
    return ~MAX_INT();
}

void test_border_constants() {
    assert(MIN_INT() == -2147483648);
    assert(MIN_INT() == 0x80000000);
    assert(MAX_INT() == 2147483647);
    assert(MAX_INT() == 0x7FFFFFFF);
}

void test_satsum() {
    // small tests
    assert(satsum(1, 2) == 3);
    assert(satsum(2, 1) == 3);
    assert(satsum(5, 0) == 5);
    assert(satsum(0, 5) == 5);
    assert(satsum(-5, 0) == -5);
    assert(satsum(0, -5) == -5);
    assert(satsum(-10, 5) == -5);
    assert(satsum(5, -10) == -5);
    assert(satsum(10, -5) == 5);
    assert(satsum(-5, 10) == 5);
    assert(satsum(1000, -1000) == 0);
    assert(satsum(-1000, 1000) == 0);
    // MAX_INT() tests
    assert(satsum(MAX_INT(), 0) == MAX_INT());
    assert(satsum(0, MAX_INT()) == MAX_INT());
    assert(satsum(MAX_INT(), MAX_INT()) == MAX_INT());
    assert(satsum(MAX_INT(), MAX_INT()) == MAX_INT());
    assert(satsum(MAX_INT(), 1000) == MAX_INT());
    assert(satsum(1000, MAX_INT()) == MAX_INT());
    assert(satsum(MAX_INT(), -1000) == MAX_INT() - 1000);
    assert(satsum(-1000, MAX_INT()) == MAX_INT() - 1000);
    assert(satsum(MAX_INT() - 1, 1) == MAX_INT());
    assert(satsum(1, MAX_INT() - 1) == MAX_INT());
    assert(satsum(MAX_INT() - 1, 2) == MAX_INT());
    assert(satsum(2, MAX_INT() - 1) == MAX_INT());
    assert(satsum(1 << 30, 1 << 30) == MAX_INT());
    assert(satsum((1 << 30) - 1, (1 << 30) - 1) == (1 << 30) - 1 + (1 << 30) - 1);
    assert(satsum((1 << 30) - 1, (1 << 30) - 1) != MAX_INT());
    // MIN_INT() tests
    assert(satsum(MIN_INT(), 0) == MIN_INT());
    assert(satsum(0, MIN_INT()) == MIN_INT());
    assert(satsum(MIN_INT(), MIN_INT()) == MIN_INT());
    assert(satsum(MIN_INT(), MIN_INT()) == MIN_INT());
    assert(satsum(MIN_INT(), -1000) == MIN_INT());
    assert(satsum(-1000, MIN_INT()) == MIN_INT());
    assert(satsum(MIN_INT(), 1000) == MIN_INT() + 1000);
    assert(satsum(1000, MIN_INT()) == MIN_INT() + 1000);
    assert(satsum(MIN_INT() + 1, -1) == MIN_INT());
    assert(satsum(-1, MIN_INT() +1) == MIN_INT());
    assert(satsum(MIN_INT() + 1, -2) == MIN_INT());
    assert(satsum(-2, MIN_INT() + 1) == MIN_INT());
    assert(satsum(-(1 << 30), -(1 << 30)) == MIN_INT());
    assert(satsum(-(1 << 30) + 1, -(1 << 30)) == -(1 << 30) + 1 - (1 << 30));
    assert(satsum(-(1 << 30) + 1, -(1 << 30)) != MIN_INT());
    // MAX_INT() + MIN_INT border tests
    assert(satsum(MAX_INT(), MIN_INT()) == -1);
    assert(satsum(MIN_INT(), MAX_INT()) == -1);
    assert(satsum(MAX_INT(), MIN_INT() + 1) == 0);
    assert(satsum(MIN_INT() + 1, MAX_INT()) == 0);
}

