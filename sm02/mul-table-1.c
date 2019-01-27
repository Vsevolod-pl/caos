#include <stdio.h>

void print_mul_table(int from, int to, int field_size) {
    int m1, m2;

    // Print the header.
    printf("%*s", field_size, "");
    for (m1 = from; m1 != to; ++m1) {
        printf(" %*d", field_size, m1);
    }
    printf("\n");

    // Print the table.
    for (m2 = from; m2 != to; ++m2) {
        // Print the left header.
        printf("%*d", field_size, m2);
        // Print products.
        for (int m1 = from; m1 != to; ++m1) {
            long long int product = m1;
            product *= m2;
            printf(" %*lld", field_size, product);
        }
        printf("\n");
    }
}

int main() {
    int a, b, n;
    if (scanf("%d%d%d", &a, &b, &n) == 3) {
        print_mul_table(a, b, n);
    }

    return 0;
}

