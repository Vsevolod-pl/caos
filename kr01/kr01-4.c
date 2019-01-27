#include <stdint.h>
#include <stdio.h>

int main() {
    uint64_t inverse[2000];
    int n;
    if (scanf("%d", &n) == 1) {
        uint64_t a, b;
        for (a = 1; a < n; ++a) {
            for (b = a; b < n; ++b) {
                if (a * b % n == 1) {
                    inverse[a] = b;
                    inverse[b] = a;
                }
            }
        }
        for (a = 0; a < n; ++a) {
            printf("%lu", a);
            for (b = 2; b < n; ++b) {
                printf(" %lu", (a * inverse[b]) % n);
            }
            printf("\n");
        }
    }
    return 0;
}

