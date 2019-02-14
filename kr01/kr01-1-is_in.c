#include <stdio.h>

int is_in(float x, float y) {
    if (x < 2) {
        return 0;
    }
    if (x > 5) {
        return 0;
    }
    if (y < 1) {
        return 0;
    }
    if (y > 7) {
        return 0;
    }
    if (y > x + 3) {
        return 0;
    }
    if (y < x - 2) {
        return 0;
    }
    return 1;
}

int main() {
    float x, y;
    if (scanf("%f%f", &x, &y) == 2) {
        printf("%d\n", is_in(x, y));
    }

    return 0;
}

