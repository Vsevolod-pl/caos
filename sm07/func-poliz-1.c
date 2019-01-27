#include "poliz.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PolizState
{
    int32_t *stack;
    size_t size, capacity;
    int first_in_line;
    int err;
};

size_t get_shift(struct PolizState *state, int iextra) {
    assert(iextra + 1 <= state->size);
    return state->size - 1 - iextra;
}

// Assume that stack is not empty.
int32_t stack_top(struct PolizState *state) {
    assert(state->size > 0);
    return *(state->stack + get_shift(state, 0));
}

// Assume that stack is not empty.
void stack_pop(struct PolizState *state) {
    assert(state->size > 0);
    --state->size;
}

// Return the error code.
int stack_push(struct PolizState *state, int32_t new_item) {
    if (state->capacity == 0) {
        state->stack = malloc(sizeof(int32_t));
        if (state->stack) {
            state->capacity = 1;
        } else {
            return PE_OUT_OF_MEMORY;
        }
    }
    if (state->capacity == state->size) {
        int32_t *new_stack = realloc(state->stack, 2 * state->capacity * sizeof(int32_t));
        if (new_stack) {
            state->stack = new_stack;
            state->capacity *= 2;
        } else {
            return PE_OUT_OF_MEMORY;
        }
    }
    *(state->stack + (state->size++)) = new_item;
    return PE_OK;
}

int32_t MAX_INT32() {
    return ~0U >> 1;
}

int32_t MIN_INT32() {
    return ~MAX_INT32();
}

int is_sum_overflow(int32_t addend_first, int32_t addend_second) {
    if (addend_first > 0 && addend_second > 0) {
        return addend_first > MAX_INT32() - addend_second;
    } else if (addend_first < 0 && addend_second < 0) {
        return addend_first < MIN_INT32() - addend_second;
    }
    return 0;
}

int is_sub_overflow(int32_t minuend, int32_t subtrahend) {
    if (subtrahend < 0 && minuend > MAX_INT32() + subtrahend) return 1;
    if (subtrahend > 0 && minuend < MIN_INT32() + subtrahend) return 1;
    return 0;
}

// Gracias to StackOverflow #199333 175 likes answer (there were some mistakes though).
int is_mult_overflow(int32_t multiplicand_first, int32_t multiplicand_second) {
    if (multiplicand_first == 0 || multiplicand_second == 0) return 0;
    if (multiplicand_first == MIN_INT32() && multiplicand_second == -1) return 1;
    if (multiplicand_first == -1 && multiplicand_second == MIN_INT32()) return 1;
    if (multiplicand_first == -1 || multiplicand_second == -1) return 0;
    if (multiplicand_second > 0) {
        if (multiplicand_first > MAX_INT32() / multiplicand_second) return 1;
        if (multiplicand_first < MIN_INT32() / multiplicand_second) return 1;
    }
    if (multiplicand_second < 0) {
        if (multiplicand_first < MAX_INT32() / multiplicand_second) return 1;
        if (multiplicand_first > MIN_INT32() / multiplicand_second) return 1;
    }
    return 0;
}

int is_div_overflow(int32_t dividend, int32_t divisor) {
    return dividend == MIN_INT32() && divisor == -1;
}

int add_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 2U) {
        int32_t addend_second = stack_top(state);
        stack_pop(state);
        int32_t addend_first = stack_top(state);
        stack_pop(state);
        if (is_sum_overflow(addend_first, addend_second)) {
            state->err = -PE_INT_OVERFLOW;
            assert(state->err < 1);
            return state->err;
        } else {
            state->err = -stack_push(state, addend_first + addend_second);
            assert(state->err < 1);
            return state->err;
        }
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}

int subtract_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 2U) {
        int32_t subtrahend = stack_top(state);
        stack_pop(state);
        int32_t minuend = stack_top(state);
        stack_pop(state);
        if (is_sub_overflow(minuend, subtrahend)) {
            state->err = -PE_INT_OVERFLOW;
            assert(state->err < 1);
            return state->err;
        } else {
            state->err = -stack_push(state, minuend - subtrahend);
            assert(state->err < 1);
            return state->err;
        }
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}

int multiply_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 2U) {
        int32_t multiplicand_second = stack_top(state);
        stack_pop(state);
        int32_t multiplicand_first = stack_top(state);
        stack_pop(state);
        if (is_mult_overflow(multiplicand_first, multiplicand_second)) {
            state->err = -PE_INT_OVERFLOW;
            assert(state->err < 1);
            return state->err;
        }
        state->err = -stack_push(state, multiplicand_first * multiplicand_second);
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}

int32_t math_div(int32_t dividend, int32_t divisor) {
    if (dividend == 0) {
        return 0;
    }
    if (dividend > 0) {
        return dividend / divisor;
    } else {
        int32_t div = dividend / divisor, mod = dividend % divisor;
        if (mod) {
            if (divisor > 0) {
                return div - 1;
            } else {
                return div + 1;
            }
        } else {
            return div;
        }
    }
}

int32_t math_mod(int32_t dividend, int32_t divisor) {
    return dividend - divisor * math_div(dividend, divisor);
}

int div_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 2U) {
        int32_t divisor = stack_top(state);
        stack_pop(state);
        int32_t dividend = stack_top(state);
        stack_pop(state);
        if (is_div_overflow(dividend, divisor)) {
            state->err = -PE_INT_OVERFLOW;
            assert(state->err < 1);
            return state->err;
        }
        if (divisor == 0) {
            state->err = -PE_DIVISION_BY_ZERO;
            assert(state->err < 1);
            return state->err;
        }
        state->err = -stack_push(state, math_div(dividend, divisor));
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}
int mod_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 2U) {
        int32_t divisor = stack_top(state);
        stack_pop(state);
        int32_t dividend = stack_top(state);
        stack_pop(state);
        if (divisor == -1) {
            state->err = -stack_push(state, 0);
        }
        if (is_div_overflow(dividend, divisor)) {
            state->err = -PE_INT_OVERFLOW;
            assert(state->err < 1);
            return state->err;
        }
        if (divisor == 0) {
            state->err = -PE_DIVISION_BY_ZERO;
            assert(state->err < 1);
            return state->err;
        }
        state->err = -stack_push(state, math_mod(dividend, divisor));
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}
int neg_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 1U) {
        int32_t new_item = stack_top(state);
        stack_pop(state);
        if (is_mult_overflow(new_item, -1)) {
            state->err = -PE_INT_OVERFLOW;
            assert(state->err < 1);
            return state->err;
        }
        state->err = -stack_push(state, -new_item);
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}
int read_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    int32_t new_item;
    if (scanf("%d", &new_item) == 1) {
        state->err = -stack_push(state, new_item);
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_READ_FAILED;
        assert(state->err < 1);
        return state->err;
    }
}
int write_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 1U) {
        fprintf(stdout, "%d", stack_top(state));
        state->first_in_line = 0;
        stack_pop(state);
        state->err = -PE_OK;
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}

int newline_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    state->first_in_line = 1;
    fprintf(stdout, "\n");
    state->err = -PE_OK;
    assert(state->err < 1);
    return state->err;
}

int pop_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (state->size >= 1U) {
        stack_pop(state);
        state->err = -PE_OK;
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_STACK_UNDERFLOW;
        assert(state->err < 1);
        return state->err;
    }
}

// default = 0
int to_top_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (iextra + 1 <= state->size) {
        state->err = -stack_push(state, *(state->stack + get_shift(state, iextra)));
        assert(state->err < 1);
        return state->err;
    } else {
        state->err = -PE_INVALID_INDEX;
        assert(state->err < 1);
        return state->err;
    }
}

// default = 1
int swap_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    if (iextra) {
        if (iextra + 1 <= state->size) {
            int shift_top = get_shift(state, 0);
            int shift_iextra = get_shift(state, iextra);
            int32_t tmp = *(state->stack + shift_top);
            *(state->stack + shift_top) = *(state->stack + shift_iextra);
            *(state->stack + shift_iextra) = tmp;
            state->err = -PE_OK;
            assert(state->err < 1);
            return state->err;
        } else {
            state->err = -PE_INVALID_INDEX;
            assert(state->err < 1);
            return state->err;
        }
    } else {
        // If 0, no action -- always PE_OK.
        state->err = -PE_OK;
        assert(state->err < 1);
        return state->err;
    }
}

int push_(struct PolizState *state, int iextra) {
    if (state->err) return -state->err;
    state->err = -stack_push(state, iextra);
    assert(state->err < 1);
    return state->err;
}

int parse_int32(const char *s, int32_t *out) {
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

void parse_command(const char *cmd, poliz_func_t *handler, int *iextra) {
    *iextra = 0;
    if (!strcmp(cmd, "+")) { *handler = &add_; }
    else if (!strcmp(cmd, "-")) { *handler = &subtract_; }
    else if (!strcmp(cmd, "*")) { *handler = &multiply_; }
    else if (!strcmp(cmd, "/")) { *handler = &div_; }
    else if (!strcmp(cmd, "%")) { *handler = &mod_; }
    else if (!strcmp(cmd, "#")) { *handler = &neg_; }
    else if (!strcmp(cmd, "r")) { *handler = &read_; }
    else if (!strcmp(cmd, "w")) { *handler = &write_; }
    else if (!strcmp(cmd, "n")) { *handler = &newline_; }
    else if (!strcmp(cmd, ";")) { *handler = &pop_; }
    else {
        // swap_, to_top_ or push_.
        // Think about default iextras! d -> d0, s -> s1
        const char *num_start = cmd;
        if (*cmd == 's') {
            *handler = &swap_;
            if (!strcmp(cmd, "s")) {
                *iextra = 1;
                return;
            }
            ++num_start;
        } else if (*cmd == 'd') {
            *handler = &to_top_;
            if (!strcmp(cmd, "d")) {
                *iextra = 0;
                return;
            }
            ++num_start;
        } else {
            *handler = &push_;
        }
        assert(parse_int32(num_start, iextra));
        return;
    }
}

enum { MAX_STRING_LENGTH = 20 };

struct PolizItem *poliz_compile(const char *str) {
    struct PolizItem *handlers = NULL;
    size_t capacity = 0, size = 0;
    const char *p = str;
    char *cmd = malloc(sizeof(char) * MAX_STRING_LENGTH);
    int cmd_size = 0;
    while (42) {
        int c = *p;
        if (isspace(c) || c == 0) {
            if (cmd_size) {
                *(cmd + cmd_size) = '\0';
                cmd_size = 0;
                if (capacity == 0) {
                    handlers = malloc(sizeof(struct PolizItem));
                    if (handlers) {
                        capacity = 1;
                    } else {
                        free(cmd);
                        return NULL;
                    }
                }
                if (capacity == size) {
                    struct PolizItem *new_handlers = realloc(
                            handlers,
                            2 * capacity * sizeof(struct PolizItem));
                    if (new_handlers) {
                        handlers = new_handlers;
                        capacity *= 2;
                    } else {
                        free(handlers);
                        free(cmd);
                        return NULL;
                    }
                }
                parse_command(cmd, &(handlers + size)->handler, &(handlers + size)->iextra);
                ++size;
            }
            if (c == 0) {
                break;
            }
        } else {
            // Non-space.
            *(cmd + (cmd_size++)) = c;
        }
        ++p;
    }
    free(cmd);
    if (capacity == 0) {
        handlers = malloc(sizeof(struct PolizItem));
        if (handlers) {
            capacity = 1;
        } else {
            return NULL;
        }
    }
    if (capacity == size) {
        struct PolizItem *new_handlers = realloc(
                handlers,
                2 * capacity * sizeof(struct PolizItem));
        if (new_handlers) {
            handlers = new_handlers;
            capacity *= 2;
        } else {
            free(handlers);
            return NULL;
        }
    }
    (handlers + size)->handler = NULL;
    (handlers + size)->iextra = 0;
    return handlers;
}

void poliz_free_state(struct PolizState *state) {
    if (state) {
        if (state->stack) {
            free(state->stack);
        }
        free(state);
    }
}

int poliz_last_error(struct PolizState *state) {
    return -state->err;
}

struct PolizState *poliz_new_state(void) {
    struct PolizState *state = malloc(sizeof(struct PolizState));
    if (state) {
        state->stack = NULL;
        state->size = 0;
        state->capacity = 0;
        state->first_in_line = 1;
        state->err = 0;
    }
    return state;
}

/*
int main() {
    // const char *str = "1 2 -1 w n w n";
    // const char *str = "+123 +123 + w n";
    // const char *str = "123 123 + w n";
    // const char *str = "r r + w n";
    // const char *str = "r r - w n";
    // const char *str = "r r * w n";
    // const char *str = "1 2147483647 / w 1 2147483647 % w n";
    // const char *str = "1 -2147483648 / w 1 -2147483648 % w n";
    // const char *str = "-1 2147483647 / w -1 2147483647 % w n";
    // const char *str = "-1   -2147483648 / w -1 -2147483648 % w n";
    // const char *str = "39 0 / w 39 0 % w n";
    // const char *str = "39 13 / w 39 13 % w n";
    // const char *str = "39 -13 / w 39 -13 % w n";
    // const char *str = "-39 13 / w -39 13 % w n";
    // const char *str = "-39 -13 / w -39 -13 % w n";
    // const char *str = "37 13 / w 37 13 % w n";
    // const char *str = "37 -13 / w 37 -13 % w n";
    // const char *str = "-37 13 / w -37 13 % w n";
    // const char *str = "-37 -13 / w -37 -13 % w n";
    // const char *str = "13 37 / w 13 37 % w n";
    // const char *str = "13 -37 / w 13 -37 % w n";
    // const char *str = "-13 37 / w -13 37 % w n";
    // const char *str = "-13 -37 / w -13 -37 % w n";
    // const char *str = "r r / w n";
    // const char *str = "r r % w n";
    // const char *str = "r r ; w n";
    // const char *str = "r # w n";
    // const char *str = "r r w w n";
    // const char *str = "r r r r r r r r w n w w w n w w w n w";
    // const char *str = "r r r r r r r r w n w w w n w w w n w n";
    // const char *str = "r r r r r r r r w w w n w n w w w n w n";
    // const char *str = "r r r r r r r r n w w w n w n w w w n w n";
    // const char *str = "1 2 3 4 -5 -6 2147483647 -2147483648 w n w n w n w n w n w n w n w n";
    // const char *str = "-2147483648 #";
    // const char *str = "-1 42 * w n";
    // const char *str = "42 -1 * w n";
    // Errors:
    // const char *str = "1 2 3 w w w w";  //PE_STACK_UNDERFLOW
    // const char *str = "1 2 ; ;";  // NO PE_STACK_UNDERFLOW
    // const char *str = "1 2 ; ; ;";  // PE_STACK_UNDERFLOW
    // const char *str = "1 2 3 s2 w s2";  // PE_INVALID_INDEX
    // const char *str = "5 -0 /";  // PE_DIVISION_BY_ZERO
    // const char *str = "5 -0 %";  // PE_DIVISION_BY_ZERO
    const char *str = "-2147483648 -2147483648 - w";
    // const char *str = "-2147483648 -1 /";  // PE_INT_OVERFLOW
    // const char *str = "-2147483648 -1 %";  // PE_INT_OVERFLOW
    // const char *str = "3 2 0 1 s  w w w w w";
    // const char *str = "3 2 1 0 s0 w w w w w";
    // const char *str = "3 2 0 1 s1 w w w w w";
    // const char *str = "3 0 1 2 s2 w w w w w";
    // const char *str = "0 2 1 3 s3 w w w w w";
    // const char *str = "0 2 1 3 s4 w w w w w";
    // const char *str = "s0";
    // const char *str = " s0     ";
    // const char *str = "3 2 0 1 0  w w w w w w";
    // const char *str = "3 2 1 0 d0 w w w w w w";
    // const char *str = "3 2 0 1 d1 w w w w w w";
    // const char *str = "3 0 1 2 d2 w w w w w w";
    // const char *str = "0 2 1 3 d3 w w w w w w";
    // const char *str = "0 2 1 3 d4 w w w w w w";
    // const char *str = "d0";
    // const char *str = "       d  ";
    // const char *str = " d0     ";
    // const char *str = ";";
    // Fancy write tests.
    // const char *str = "100 128 + w n";
    // const char *str = "1 w";
    // const char *str = "1 w n";
    // const char *str = "1 2 w w";
    // const char *str = "1 2 w w n";
    // const char *str = "1 2 w n w";
    // const char *str = "1 2 w n w n";
    // const char *str = "1 2 3 4 w w w w";
    // const char *str = "1 2 3 4 w w w w n";
    // const char *str = "1 2 3 4 w n w w w ";
    // const char *str = "1 2 3 4 w n w w w n ";
    // const char *str = "1 2 3 4 w w n w w ";
    // const char *str = "1 2 3 4 w w n w w n ";
    // const char *str = "1 2 3 4 w w w n w ";
    // const char *str = "1 2 3 4 w w w n w n ";
    // const char *str = "1 2 3 4 w n w n w n w";
    // const char *str = "1 2 3 4 w n w n w n w n";
    struct PolizItem *items = poliz_compile(str);
    struct PolizState *state = poliz_new_state();
    for (int i = 0; items[i].handler != NULL; ) {
        int err = items[i].handler(state, items[i].iextra);
        if (err < 0) {
            fprintf(stderr, "error: %d\n", -err);
            break;
        } else if (err > 0) {
            i = err;
        } else {
            ++i;
        }
    }
    poliz_free_state(state);
    free(items);
    return 0;
}
*/

