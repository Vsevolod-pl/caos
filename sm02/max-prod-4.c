#include <stdio.h>

int main() {
    int max1, max2, new_item;
    if (scanf("%d%d", &max1, &max2) == 2) {
        if (max1 < max2) {
            int temp = max1;
            max1 = max2;
            max2 = temp;
        }
        while (scanf("%d", &new_item) == 1) {
            if (new_item >= max1) {
                max2 = max1;
                max1 = new_item;
            } else {
                if (new_item > max2) {
                    max2 = new_item;
                }
            }
        }
    }

    printf("%d\n", max1 * max2);

    return 0;
}

