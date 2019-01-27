#include <stdio.h>

int main() {
    int n, w;
    if (scanf("%d%d", &n, &w) == 2) {

    }
    unsigned int i, max_number = (1U << n) - 1;
    for (i = 0; i <= max_number; ++i) {
        printf("|");
        printf("%*x", w, i);
        printf("|");
        printf("%*u", w, i);
        printf("|");
        if (i >> (n - 1)) {
            printf("%*d", w, (int) (~0U >> n << n) | i);
        } else {
            printf("%*d", w, i);
        }
        printf("|\n");
    }

    return 0;
}

