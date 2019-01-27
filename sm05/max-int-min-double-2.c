#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_STRING_LENGTH = 63 };

char get_char(int is_input_file, FILE *stream) {
    if (is_input_file) {
        return fgetc_unlocked(stream);
    } else {
        return getchar_unlocked();
    }
}

int is_char_correct(char c) {
    if (c == '\t' || c == '\n' || c == '\r') {
        return 1;
    }
    if ((0 <= c && c <= 31) || c == 127) {
        return 0;
    }
    return 1;
}

int parse_int32(char *s, int32_t *out) {
    char *eptr;
    errno = 0;
    int64_t value = strtol(s, &eptr, 10);
    if (!*s || *eptr || errno) {
        return 0;
    }
    if (value == (int32_t)value) {
        *out = (int32_t)value;
        return 1;
    } else {
        return 0;
    }
}

int parse_double(char *s, double *out) {
    int only_digits = 1;
    char *s_copy = s;
    if (!*s) {
        return 0;
    }
    if (*s_copy == '+' || *s_copy == '-') {
        ++s_copy;
    }
    for (; *s_copy; ++s_copy) {
        if (isdigit(*s_copy)) {
            continue;
        }
        only_digits = 0;
        break;
    }
    if (only_digits) {
        return 0;
    }
    char *eptr;
    errno = 0;
    double value = strtod(s, &eptr);
    if (!*s || *eptr || errno) {
        return 0;
    }
    *out = value;
    return 1;
}

int main(int argc, char* argv[]) {
    FILE *stream = NULL;
    int is_input_file = 0;
    if (argc > 2) {
        fprintf(stderr, "too many arguments\n");
        return 1;
    }
    if (argc > 1) {
        is_input_file = 1;
        if (!(stream = fopen(argv[1], "r"))) {
            fprintf(stderr, "error of fopen()\n");
            return 1;
        }
    }
    int32_t max_int = 0;
    double min_double = 0.0;
    size_t string_size = 0;
    int c;
    int is_int_found = 0, is_double_found = 0, is_nan_found = 0;
    char *s = malloc(sizeof(char) * (MAX_STRING_LENGTH + 1));
    if (!s) {
        fprintf(stderr, "malloc() for string failed\n");
        return 1;
    }
    while (42) {
        c = get_char(is_input_file, stream);
        if (!is_char_correct(c) && c != EOF) {
            fprintf(stderr, "invalid characters in input\n");
            free(s);
            return 1;
        }
        if (c == EOF || isspace(c)) {
            if (string_size) {
                // 0-terminate a string.
                *(s + string_size) = '\0';
                string_size = 0;
                // Parse a string.
                int32_t int_value = 0;
                if (parse_int32(s, &int_value)) {
                    if (is_int_found) {
                        if (max_int < int_value) {
                            max_int = int_value;
                        }
                    } else {
                        // It's the first int number in the input.
                        is_int_found = 1;
                        max_int = int_value;
                    }
                    if (c == EOF) {
                        break;
                    } else {
                        continue;
                    }
                }
                double double_value = 0;
                if (parse_double(s, &double_value)) {
                    if (!is_nan_found) {
                        if (isnan(double_value)) {
                            is_nan_found = 1;
                            is_double_found = 1;
                            min_double = NAN;
                        } else if (is_double_found) {
                            if (min_double > double_value) {
                                min_double = double_value;
                            }
                        } else {
                            // It's the first double number in the input.
                            is_double_found = 1;
                            min_double = double_value;
                        }
                    }
                    if (c == EOF) {
                        break;
                    } else {
                        continue;
                    }
                }
            }
            if (c == EOF) {
                break;
            } else {
                continue;
            }
        } else {
            if (string_size == MAX_STRING_LENGTH) {
                fprintf(stderr, "string size > %d\n", MAX_STRING_LENGTH);
                free(s);
                return 1;
            } else {
                // Add char to string.
                *(s + (string_size++)) = c;
            }
        }
    }
    if (!is_int_found) {
        fprintf(stderr, "int number not found\n");
        free(s);
        return 1;
    }
    if (!is_double_found) {
        fprintf(stderr, "double number not found\n");
        free(s);
        return 1;
    }
    fprintf(stdout, "%d %.10g\n", max_int, min_double);
    free(s);

    return 0;
}

