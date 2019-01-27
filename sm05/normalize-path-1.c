#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char SLASH = '/';

void normalize_path(char *buf) {
    if (!buf || *buf == '\0') {
        return;
    }
    char *out = buf, *start = buf;
    int is_cumulating_slashes = 0;
    while (*buf) {
        if (*buf == SLASH) {
            ++buf;
            is_cumulating_slashes = 1;
        } else {
            if (is_cumulating_slashes) {
                *out++ = SLASH;
            }
            is_cumulating_slashes = 0;
            *out++ = *buf++;
        }
    }
    if (is_cumulating_slashes) {
        *out++ = SLASH;
    }
    *out = '\0';
    buf = start;
}

