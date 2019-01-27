#include <stdint.h>
#include <stdio.h>

enum { BLOCK_SIZE = 7, OCTET_SIZE = 8 };

int main() {
    uint32_t n;
    while (scanf("%u", &n) == 1) {
        if (n == 0) {
            printf("%02x\n", n);
        }
        while (n) {
            uint32_t block;
            block = n & ((1U << (OCTET_SIZE)) - 1);
            n >>= BLOCK_SIZE;
            if (n) {
                block |= 1U << BLOCK_SIZE;
                printf("%02x ", block);
            } else {
                printf("%02x\n", block);
                break;
            }
        }
    }
    return 0;
}

