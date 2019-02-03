#include <stdint.h>

int MAX_NOT_INF() {
    return 0x10000U - 0x10U - 1U;
}

int MIN_NOT_INF() {
    return -MAX_NOT_INF();
}

int get_left_1(uint32_t v) {
    int counter = 0;
    while (v) {
        v >>= 1;
        ++counter;
    }
    return counter - 1;
}

unsigned short GET_POSITIVE_INF() {
    return 0x7c00;
}

enum { BIAS = 15U, MANTISSA_SIZE = 10, EXP_SIZE = 5 };

enum { MINUS_OR_MASK = 0x8000, NO_MANTISSA_MSB_XOR_MASK = 0x400 };

uint32_t round_to_place(uint32_t v, int place) {
    v += 1U << (place - 1);
    v >>= place;
    return v;
}

void to_half_float(int value, unsigned short *hf) {
    if (value > MAX_NOT_INF() || value < MIN_NOT_INF()) {
        *hf = GET_POSITIVE_INF();
        if (value < 0) {
            *hf |= MINUS_OR_MASK;
        }
        return;
    }
    if (value == 0) {
        *hf = 0;
        return;
    }
    *hf ^= *hf;
    if (value < 0) {
        value *= -1;
        *hf |= MINUS_OR_MASK;
    }
    uint32_t abs_value = value;
    uint32_t left_1 = get_left_1(abs_value);
    uint32_t mantissa = abs_value;
    int exp = left_1;
    if (left_1 <= MANTISSA_SIZE) {
        mantissa <<= MANTISSA_SIZE - left_1;
    } else {
        mantissa = round_to_place(mantissa, left_1 - MANTISSA_SIZE);
    }
    mantissa ^= NO_MANTISSA_MSB_XOR_MASK;
    *hf |= mantissa;
    *hf |= (exp + BIAS) << MANTISSA_SIZE;
    return;
}

#include <stdio.h>

int main() {
    int n;
    unsigned short result;
    while (scanf("%d", &n) == 1) {
        to_half_float(n, &result);
        printf("%x\n", result);
    }
}

