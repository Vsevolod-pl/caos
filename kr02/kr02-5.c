enum { BLOCK_SIZE = 16 };

int get_left_1(unsigned short v) {
    int counter = 0;
    while (v ^ 0) {
        v >>= 1;
        ++counter;
    }
    return counter - 1;
}

int get_right_1(unsigned short v) {
    int counter = 0;
    while (!(v & 1)) {
        v >>= 1;
        ++counter;
    }
    return counter;
}

enum { HF_SIGNIFICAND_BYTE_SIZE = 10U, BIAS = 15, MANTISSA_SIZE = 10, EXP_SIZE = 5 };

unsigned short round_value(unsigned short value) {
    uint32_t fractional = value & ((1U << (get_left_1(value) - HF_SIGNIFICAND_BYTE_SIZE)) - 1);
    while () {
    }
}

void to_half_float(int value, unsigned short *hf) {
    if (...) {
        *hf = POS_INF();
        return;
    }
    if (...) {
        *hf = NEG_INF();
        return;
    }
    unsigned short hf_value = 0;
    if (value < 0) {
        hf_value |= 1U << (BLOCK_SIZE - 1);
        value *= -1;
        // It's normalized anyway.
        uint32_t right1 = get_right_1(value);
        if (!is_uint_fit(value)) {
            value = round_value(value, right1);
        }
        uint32_t right1 = get_right_1(value);
        uint32_t left1 = get_left_1(value);
        uint32_t exp = right1 + BIAS;
        value ^= 1U << left1;
        uint32_t mantissa = value >> right1;
        *hf_value |= (exp << MANTISSA_SIZE);
        *hf_value |= mantissa;
    }
    *hf = hf_value;
    return;
}

int is_uint_fit(unsigned short v) {
    if (v == 0U) {
        return 1;
    }
    return get_left_1(v) - get_right_1(v) <= HF_SIGNIFICAND_BYTE_SIZE;
}

int main() {
    int n;
    unsigned short *hf = malloc(sizeof(unsigned short));
    while (scanf() == 1) {
        to_half_float(n, hf);
        printf("%x\n", *hf);
    }
    free(hf);
    return 0;
}

