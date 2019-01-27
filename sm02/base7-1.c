#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

enum { BASE = 7 };

int main() {
    int is_processing = 0, was_point = 0;
    double integer_part = 0, fractional_part = 0, exponent = 1.0 / BASE;
    int c = 0;
    while (1) {
        c = getchar_unlocked();
        if (isdigit(c)) {
            if (is_processing) {
                if (was_point) {
                    fractional_part = fractional_part + (c - '0') * exponent;
                    exponent /= BASE;
                } else {
                    integer_part = integer_part * BASE + (c - '0');
                }
            } else {
                // It's a new number!
                is_processing = 1;
                integer_part = c - '0';
            }
        } else {
            if (c == '.') {
                was_point = 1;
                exponent = 1.0 / BASE;
            } else {
                // Render the number (if is processing) and print it.
                if (is_processing) {
                    printf("%.10g\n", integer_part + fractional_part);
                    integer_part = 0;
                    fractional_part = 0;
                    was_point = 0;
                    is_processing = 0;
                }
            }
            if (c == EOF) {
                break;
            }
        }
    }
}

