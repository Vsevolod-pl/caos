#include <stdint.h>
#include <stdio.h>

extern void mul64p(uint64_t, uint64_t);

int main() {
    uint64_t x, y;
    if (scanf("%llu%llu", &x, &y) == 2) {
        mul64p(x, y);
    }
    return 0;
}

