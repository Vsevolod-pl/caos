#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

int is_int32_t(struct Elem *item, int32_t *value) {
    char *eptr;
    errno = 0;
    int64_t test_value = strtol(item->str, &eptr, 10);
    if (!*(item->str) || *eptr || errno) {
        return 0;
    } else if (test_value == (int32_t)test_value) {
        *value = test_value;
        return 1;
    } else {
        // Too big for int32_t.
        return 0;
    }
}

enum { MAX_INT32_LENGTH = 11 };

int32_t MAX_INT32() {
    return ~0U >> 1;
}

int32_t MIN_INT32() {
    return ~MAX_INT32();
}

struct Elem *dup_elem(struct Elem *head) {
    // Check for empty list.
    if (!head) {
        return head;
    }
    struct Elem *prev = NULL, *current = head;
    int32_t value;
    while (current) {
        if (is_int32_t(current, &value) && value != MIN_INT32()) {
            struct Elem *new_item = malloc(sizeof(struct Elem));
            if (current == head) {
                head = new_item;
            } else {
                prev->next = new_item;
            }
            new_item->next = current;
            new_item->str = malloc(sizeof(char) * (MAX_INT32_LENGTH + 1));
            sprintf(new_item->str, "%d", value - 1);
        }
        prev = current;
        current = current->next;
    }
    return head;
}

