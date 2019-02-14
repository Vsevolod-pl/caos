#include <stdio.h>
#include "kr03-4.c"

int main() {
    char *strings[24] = {
        "", "2147483647", "2147483648", "-2147483647", "-2147483648", "-2147483649",
        "+10", "+10 ", " +10",
        "+ 10", "+ 10 ", " + 10",
        "10", "10 ", " 10",
        "-10", "-10 ", " -10",
        "-03", "-03 ", " -03",
        "alpha", "5x",
    };
    struct Elem test[19];
    test[0].next = &test[1];
    test[1].next = &test[2];
    test[2].next = &test[3];
    test[3].next = &test[4];
    test[4].next = &test[5];
    test[5].next = &test[6];
    test[6].next = &test[7];
    test[7].next = &test[8];
    test[8].next = &test[9];
    test[9].next = &test[10];
    test[10].next = &test[11];
    test[11].next = &test[12];
    test[12].next = &test[13];
    test[13].next = &test[14];
    test[14].next = &test[15];
    test[15].next = &test[16];
    test[16].next = &test[17];
    test[17].next = &test[18];
    test[18].next = NULL;
    for (int i = 0; i != 19; ++i) {
        test[i].str = strings[i];
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

