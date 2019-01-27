#include <stdio.h>

union FU
{
    float fv;
    struct {
        unsigned m:23;
        unsigned e:8;
        unsigned s:1;
    };
};

int main() {
    union FU u;
    while (scanf("%f", &u.fv) == 1) {
        printf("%u %u %x\n", u.s, u.e, u.m);
    }

    return 0;
}

