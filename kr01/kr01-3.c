#include <ctype.h>
#include <stdio.h>

unsigned int convert(unsigned int c) {
    c ^= (1U << 3);
    c &= ~(1U << 2);
    return c;
}

char print_code(unsigned int c) {
    if (c == 0) {
        return '@';
    }
    if (c == 63) {
        return '#';
    }
    if (c <= 10) {
        return '0' + (c - 1);
    }
    if (c <= 36) {
        return 'a' + (c - 1 - 10);
    }
    return 'A' + (c - 1 - 10 - 26);
}

unsigned int char_to_code(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0' + 1;
    }
    if ('a' <= c && c <= 'z') {
        return c - 'a' + 1 + 10;
    }
    return c - 'A' + 1 + 10 + 26;
}

int main() {
    int c;
    while ((c = getchar_unlocked()) != EOF) {
        if (isalnum(c)) {
            unsigned int code = char_to_code(c);
            code = convert(code);
            printf("%c", print_code(code));
        }
    }
    printf("\n");

    return 0;
}

