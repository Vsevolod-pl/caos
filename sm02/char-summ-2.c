#include <stdio.h>

int FIRST_DIGIT = '0', LAST_DIGIT = '9';

int main() {
    int c, digit_sum = 0;
    while ((c = getchar_unlocked()) != EOF) {
        if (FIRST_DIGIT <= c && c <= LAST_DIGIT) {
            digit_sum += c - '0';
        }
    }
    printf("%d\n", digit_sum);

    return 0;
}

