#include <errno.h>

struct Elem *dup_elem(struct Elem *head) {
    char *eptr;
    errno = 0; // очищаем errno, так как при успехе errno не модифицируется
    long value = strtol(str, &eptr, 10);
    if (!*str || *eptr || errno) {
        // ошибка преобразования из строки в число
    }
}

