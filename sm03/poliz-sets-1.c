#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

const char MIN_DIGIT = '0';
const char MIN_BIG_LETTER = 'A';
const char MIN_SMALL_LETTER = 'a';
const int ALPHABET_LENGTH = 26;
const int NUM_DIGITS = 10;
const int MAX_SHIFT = 61;
const size_t MAX_STACK_SIZE = 1000;

uint64_t char_to_mask(char c) {
    uint64_t mask = 1U;
    if (MIN_DIGIT <= c && c < MIN_DIGIT + NUM_DIGITS) {
        return mask << (c - '0');
    }
    if (MIN_BIG_LETTER <= c && c < MIN_BIG_LETTER + ALPHABET_LENGTH) {
        return mask << (c - MIN_BIG_LETTER + NUM_DIGITS);
    }
    if (MIN_SMALL_LETTER <= c && c < MIN_SMALL_LETTER + ALPHABET_LENGTH) {
        return mask << (c - MIN_SMALL_LETTER + ALPHABET_LENGTH + NUM_DIGITS);
    }
    return mask;
}

void add_char_to_set(uint64_t *set, unsigned char c) {
    if (c == '#') {
        return;
    }
    *set |= char_to_mask(c);
}

char shift_to_char(int shift) {
    // Digits.
    if (shift < NUM_DIGITS) {
        return '0' + shift;
    }
    // Capital letters.
    if (shift < NUM_DIGITS + ALPHABET_LENGTH) {
        return 'A' + (shift - NUM_DIGITS);
    }
    // Small letters;
    return 'a' + (shift - NUM_DIGITS - ALPHABET_LENGTH);
}

void test_shift_to_char() {
    assert(shift_to_char(0) == '0');
    assert(shift_to_char(5) == '5');
    assert(shift_to_char(9) == '9');
    assert(shift_to_char(10) == 'A');
    assert(shift_to_char(19) == 'J');
    assert(shift_to_char(35) == 'Z');
    assert(shift_to_char(36) == 'a');
    assert(shift_to_char(45) == 'j');
    assert(shift_to_char(61) == 'z');
    fprintf(stderr, "shift_to_char() -> OK\n");
}

void test_add_char_to_set() {
    // Digits.
    uint64_t set = 0ULL;
    add_char_to_set(&set, '0');
    assert(set == 1ULL);
    add_char_to_set(&set, '1');
    assert(set == 3ULL);
    add_char_to_set(&set, '1');
    assert(set == 3ULL);

    set = 0ULL;
    add_char_to_set(&set, '5');
    assert(set == 32ULL);
    add_char_to_set(&set, '9');
    assert(set == (1ULL << 5) + (1ULL << 9));
    fprintf(stderr, "Digits -> OK\n");

    // Capital letters.
    set = 0ULL;
    add_char_to_set(&set, 'A');
    assert(set == (1ULL << 10));
    set = 0ULL;
    add_char_to_set(&set, 'J');
    assert(set == (1ULL << 19));
    set = 0ULL;
    add_char_to_set(&set, 'Z');
    assert(set == (1ULL << 35));
    fprintf(stderr, "Capital letters -> OK\n");

    // Small letters.
    set = 0ULL;
    add_char_to_set(&set, 'a');
    assert(set == (1ULL << 36));
    set = 0ULL;
    add_char_to_set(&set, 'j');
    assert(set == (1ULL << 45));
    set = 0ULL;
    add_char_to_set(&set, 'z');
    assert(set == (1ULL << 61));
    fprintf(stderr, "Small letters -> OK\n");

    // Full subset.
    set = 0ULL;
    for (unsigned char c = '0'; c <= '9'; ++c) {
        add_char_to_set(&set, c);
    }
    assert(set == (1ULL << 10) - 1);
    set = 0ULL;
    for (unsigned char c = 'A'; c <= 'Z'; ++c) {
        add_char_to_set(&set, c);
    }
    assert(set == (1ULL << 36) - (1ULL << 10));
    set = 0ULL;
    for (unsigned char c = 'a'; c <= 'z'; ++c) {
        add_char_to_set(&set, c);
    }
    assert(set == (1ULL << 62) - (1ULL << 36));
    for (unsigned char c = 'a'; c <= 'z'; ++c) {
        add_char_to_set(&set, c);
    }
    assert(set == (1ULL << 62) - (1ULL << 36));
    fprintf(stderr, "Subsets -> OK\n");

    // All 62 characters.
    set = 0ULL;
    for (unsigned char c = '0'; c <= '9'; ++c) {
        add_char_to_set(&set, c);
    }
    for (unsigned char c = 'A'; c <= 'Z'; ++c) {
        add_char_to_set(&set, c);
    }
    for (unsigned char c = 'a'; c <= 'z'; ++c) {
        add_char_to_set(&set, c);
    }
    assert(set == (1ULL << 62) - 1);
    fprintf(stderr, "Full 62 items set -> OK\n");
}

void test_char_to_mask() {
    assert(char_to_mask('0') == 1U);
    assert(char_to_mask('2') == 4U);
    assert(char_to_mask('8') == 256U);
    assert(char_to_mask('9') == 512U);
    assert(char_to_mask('A') == 1024U);
    assert(char_to_mask('B') == 2048U);
    assert(char_to_mask('Z') == 34359738368U);
    assert(char_to_mask('a') == 68719476736U);
    assert(char_to_mask('b') == 137438953472U);
    assert(char_to_mask('z') == 2305843009213693952U);
    fprintf(stderr, "char_to_mask() -> OK\n");
}

void print_set(uint64_t set) {
    if (set == 0ULL) {
        printf("#\n");
        return;
    }
    for (int shift = 0; shift <= MAX_SHIFT; ++shift) {
        if (set & (1ULL << shift)) {
            printf("%c", shift_to_char(shift));
        }
    }
    printf("\n");
}

int main() {
    /*
    test_shift_to_char();
    test_char_to_mask();
    test_add_char_to_set();
    */
    uint64_t stack[MAX_STACK_SIZE], set = 0;
    size_t stack_size = 0;
    int c, is_processing = 0;
    while ((c = getchar_unlocked()) != EOF) {
        if (isalnum(c) || c == '#') {
            if (!is_processing) {
                is_processing = 1;
                set = 0;
            }
            add_char_to_set(&set, c);
            continue;
        }
        if (isspace(c)) {
            if (is_processing) {
                is_processing = 0;
                stack[stack_size++] = set;
            }
            continue;
        }
        if (c == '|') {
            stack[stack_size - 2] |= stack[stack_size - 1];
            --stack_size;
            continue;
        }
        if (c == '^') {
            stack[stack_size - 2] ^= stack[stack_size - 1];
            --stack_size;
            continue;
        }
        if (c == '&') {
            stack[stack_size - 2] &= stack[stack_size - 1];
            --stack_size;
            continue;
        }
        if (c == '~') {
            stack[stack_size - 1] = ~stack[stack_size - 1];
            stack[stack_size - 1] <<= 64 - MAX_SHIFT - 1;
            stack[stack_size - 1] >>= 64 - MAX_SHIFT - 1;
            continue;
        }
    }
    print_set(stack[0]);
    return 0;
}

