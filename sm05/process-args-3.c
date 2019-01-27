#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int parse(char *arg) {
    char *eptr;
    errno = 0;
    int64_t value = strtol(arg, &eptr, 10);
    if (!*arg || *eptr || errno) {
        return -1;
    }
    if (value == (int8_t)value) {
        return 1;
    }
    if (value == (int16_t)value) {
        return 2;
    }
    if (value == (int32_t)value) {
        return 4;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    size_t i;
    for (i = 1; i != argc; ++i) {
        printf("%d\n", parse(argv[i]));
    }
}

