#include <stdio.h>

int main() {
    unsigned int offset;
    while (scanf("%x", &offset) == 1) {
        for (int number_id = 0; number_id != 4; ++number_id) {
            unsigned int v[4];
            int scanf_result = scanf("%x%x%x%x", &v[0], &v[1], &v[2], &v[3]);
            if (scanf_result != 4) {
                break;
            }
            unsigned int number = 0;
            for (int octet_id = 0; octet_id != 4; ++octet_id) {
                number = (number << 8) + v[octet_id];
            }
            printf("%u\n", number);
        }
    }
    return 0;
}

