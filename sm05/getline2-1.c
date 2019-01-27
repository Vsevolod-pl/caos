#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *getline2(FILE *f) {
    int c;
    char *begin = NULL, *new_begin = NULL;
    uint64_t capacity = 0, size = 0;
    while ((c = fgetc_unlocked(f)) != EOF) {
        if (capacity == 0) {
            begin = malloc(sizeof(*begin));
            if (begin) {
                capacity = 1;
            } else {
                return NULL;
            }
        }
        if (capacity == size) {
            new_begin = realloc(begin, 2 * capacity * sizeof(*begin));
            if (new_begin) {
                begin = new_begin;
                capacity <<= 1;
            } else {
                free(begin);
                return NULL;
            }
        }
        *(begin + size) = c;
        ++size;
        if (c == '\n') {
            break;
        }
    }
    if (size == 0) {
        return NULL;
    }
    if (capacity == size) {
        new_begin = realloc(begin, 2 * capacity * sizeof(*begin));
        if (new_begin) {
            begin = new_begin;
            capacity <<= 1;
        } else {
            free(begin);
            return NULL;
        }
    }
    *(begin + size) = 0;
    ++size;
    return begin;
}

