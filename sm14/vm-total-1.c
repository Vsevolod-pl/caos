#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum { MAX_LINE_LENGTH = 49 + 42 + PATH_MAX };

int main() {
    char *buf = malloc(MAX_LINE_LENGTH);
    uint64_t sum = 0;
    uint32_t left, right;
    if (!buf) {
        return 0;
    }
    while (fgets(buf, MAX_LINE_LENGTH, stdin) != NULL) {
        if (sscanf(buf, "%x-%x", &left, &right) == 2) {
            sum += right;
            sum -= left;
        }
    }
    printf("%lu\n", sum);
    free(buf);
    return 0;
}

