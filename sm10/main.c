#include <stdio.h>
#include <stdlib.h>

extern void myhypot(double x, double y, double *r);

int main() {
    double x, y, r = 42.0;
    if (scanf("%lf%lf", &x, &y) == 2) {
        myhypot(x, y, &r);
        printf("%.10g\n", r);
    }
    return 0;
}

