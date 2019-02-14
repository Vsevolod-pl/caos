#include <stdio.h>
#include <stdlib.h>
#include "kr03-5.c"

void simple_compare_cc(int v1, int v2, void (*cc)(int result, void *cntx), void *cntx)
{
    cc(v1 - v2, cntx);
    abort();
}

void simple_print_cc(int *sorted_data, int sorted_size, void *cntx)
{
    printf("%s\n", (char*) cntx);
    for (int i = 0; i < sorted_size; ++i) {
        printf("%d\n", sorted_data[i]);
    }
    exit(0);
}

int main()
{
    int n;
    int errcode = scanf("%d", &n);
    if (errcode != 1) {
        abort();
    }
    int *arr = calloc(n, sizeof(*arr));
    for (int i = 0; i < n; ++i) {
        errcode = scanf("%d", &arr[i]);
        if (errcode != 1) {
            abort();
        }
    }
    sort_with_cc(arr, n, simple_compare_cc, simple_print_cc, "100500");
    // should never get here
    abort();
}

