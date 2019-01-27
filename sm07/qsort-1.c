#include <stdlib.h>

int compare(const void *p1, const void *p2, void *user) {
    const int *data = (const int *)user;
    int i1 = *(const int *)p1, i2 = *(const int *)p2;
    int d1 = data[i1], d2 = data[i2];
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;
    return i1 - i2;
}

void process(const size_t count, const int *data, int *order) {
    if (!count) {
        return;
    }
    int i;
    for (i = (int)count - 1; i > 0; --i) {
        order[i] = i;
    }
    order[0] = 0;
    qsort_r(order, count, sizeof(*order), compare, (void *)data);
}

