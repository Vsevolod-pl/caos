#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t interval_length(char *arg) {
    char *pt;
    int32_t left = 0, right = 0;
    int first_number = 1;
    pt = strtok(arg, ",");
    while (pt) {
        int32_t a = atoi(pt);
        if (first_number) {
            left = a;
            right = a;
            first_number = 0;
        } else {
            if (a < left) {
                left = a;
            }
            if (a > right) {
                right = a;
            }
        }
        pt = strtok(NULL, ",");
    }
    int64_t left_big = left;
    int64_t right_big = right;
    return (right_big - left_big + 1);
}

int main(int argc, char *argv[]) {
    size_t i = 0;
    for (i = 1; i != argc; ++i) {
        printf("%llu\n", interval_length(argv[i]));
    }
    return 0;
}

