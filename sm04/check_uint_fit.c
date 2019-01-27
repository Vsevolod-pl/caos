#include <stdint.h>
#include <stdio.h>

int main() {
    uint32_t two_in_20 = ((1U << 20) + 1);
    uint32_t two_in_21 = ((1U << 21) + 1);
    uint32_t two_in_22 = ((1U << 22) + 1);
    uint32_t two_in_23 = ((1U << 23) + 1);
    uint32_t two_in_24 = ((1U << 24) + 1);
    printf("%u\n", (uint32_t)(float)two_in_23);
    printf("%u\n", (uint32_t)(float)two_in_24);
    printf("%d\n", two_in_20 == ((uint32_t)(float)two_in_20));
    printf("%d\n", two_in_21 == ((uint32_t)(float)two_in_21));
    printf("%d\n", two_in_22 == ((uint32_t)(float)two_in_22));
    printf("%d\n", two_in_23 == ((uint32_t)(float)two_in_23));
    printf("%d\n", two_in_24 == ((uint32_t)(float)two_in_24));
}

