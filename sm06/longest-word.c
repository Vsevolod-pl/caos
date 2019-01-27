#include <stdio.h>
#include <stdlib.h>

enum { MAX_NUM_OCTETS = 4 };

int SHIFTS[MAX_NUM_OCTETS] = { 7, 5, 4, 3 };
int PREFIXES[MAX_NUM_OCTETS] = { 0x00, 0x06, 0x0E, 0x1E };

enum { LAST_SPACE_CODE = 0x20 };

int eval_num_octets(unsigned char c) {
    for (int i = 0; i != MAX_NUM_OCTETS; ++i) {
        if ((c >> SHIFTS[i]) == PREFIXES[i]) {
            return i + 1;
        }
    }
    return 0;
}

int is_unicode_space(char c) {
    return (unsigned char)c <= LAST_SPACE_CODE;
}

void add_null(char **s, size_t *size, size_t *capacity) {
    if (*size == *capacity) {
        char *new_s = realloc(*s, (*capacity + 1) * sizeof(char));
        if (new_s) {
            ++(*capacity);
            *s = new_s;
        }
    }
    *(*s + *size) = 0;
    ++(*size);
}

int main() {
    char octets[MAX_NUM_OCTETS];
    int c;
    size_t max_word_length = 0, current_word_length = 0;
    char *max_word = NULL, *current_word = NULL;
    size_t current_size = 0, current_capacity = 0;
    while (42) {
        c = getchar_unlocked();
        if (c == EOF || is_unicode_space(c)) {
            if (max_word_length < current_word_length) {
                add_null(&current_word, &current_size, &current_capacity);
                if (max_word) {
                    free(max_word);
                }
                max_word = current_word;
                current_word = NULL;
                max_word_length = current_word_length;
            } else {
                if (current_word) {
                    free(current_word);
                }
            }
            current_word = NULL;
            current_size = 0;
            current_capacity = 0;
            current_word_length = 0;
            if (c == EOF) {
                break;
            }
        } else {
            octets[0] = c;
            int num_octets;
            if (!(num_octets = eval_num_octets(octets[0]))) {
                fprintf(stderr, "invalid prefix\n");
                if (max_word) {
                    free(max_word);
                }
                if (current_word) {
                    free(current_word);
                }
                return 1;
            }
            for (int i = 1; i != num_octets; ++i) {
                if ((c = getchar_unlocked()) != EOF) {
                    octets[i] = c;
                } else {
                    fprintf(stderr, "getchar_unlocked() failed\n");
                    if (max_word) {
                        free(max_word);
                    }
                    if (current_word) {
                        free(current_word);
                    }
                    return 1;
                }
            }
            ++current_word_length;
            if (current_size + num_octets > current_capacity) {
                if (current_capacity == 0) {
                    current_word = malloc(MAX_NUM_OCTETS * sizeof(char));
                    if (current_word) {
                        current_capacity = MAX_NUM_OCTETS;
                    } else {
                        fprintf(stderr, "malloc() failed\n");
                        if (max_word) {
                            free(max_word);
                        }
                        if (current_word) {
                            free(current_word);
                        }
                        return 1;
                    }
                }
                char *new_current_word = realloc(current_word, 2 * current_capacity * sizeof(char));
                if (new_current_word) {
                    current_word = new_current_word;
                    current_capacity <<= 1;
                } else {
                    fprintf(stderr, "realloc() failed\n");
                    if (max_word) {
                        free(max_word);
                    }
                    if (current_word) {
                        free(current_word);
                    }
                    return 1;
                }
            }
            for (int i = 0; i != num_octets; ++i) {
                *(current_word + (current_size++)) = octets[i];
            }
        }
    }
    printf("%zu\n", max_word_length);
    if (max_word_length) {
        printf("%s\n", max_word);
    }
    if (max_word) {
        free(max_word);
    }
    if (current_word) {
        free(current_word);
    }

    return 0;
}

