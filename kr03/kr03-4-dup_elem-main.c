#include <stdio.h>
#include "kr03-4.c"

int main() {
    char *strings[] = {
        "", "2147483647", "2147483648", "-2147483647", "-2147483648", "-2147483649",
        "+10", "+10 ", " +10",
        "+ 10", "+ 10 ", " + 10",
        "10", "10 ", " 10",
        "-10", "-10 ", " -10",
        "-03", "-03 ", " -03",
        "alpha", "5x",
    };

    struct Elem test[19];
    int i;
    for (i = 0; i != 18; ++i) {
        test[i].next = &test[i + 1];
    }
    test[i].next = NULL;

    for (int j = 0; j != i + 1; ++j) {
        test[j].str = strings[j];
    }
    struct Elem *new_head = dup_elem(&test[0]);

    printf("c'mon!\n");
    for (struct Elem *it = new_head; it;) {
        printf("\"%s\"\n", it->str);
        struct Elem *next_item = it->next;
        // free(it->str);
        // free(it);
        it = next_item;
    }
}

