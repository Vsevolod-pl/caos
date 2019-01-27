// #include <assert.h>
// #include <math.h>
#include <stdint.h>
// #include <stdio.h>

union FU
{
    float fvalue;
    struct {
        unsigned mantissa:23;
        unsigned exponent:8;
        unsigned sign:1;
    };
};

FPClass fpclassf(float value, int *psign) {
    union FU u;
    u.fvalue = value;
    *psign = u.sign;
    if (u.exponent == 0xff) {
        // NaN or +-INF.
        if (u.mantissa) {
            *psign = 0;
            return FFP_NAN;
        } else {
            return FFP_INF;
        }
    } else {
        if (u.exponent == 0) {
            // +-0 or denormal.
            if (u.mantissa) {
                return FFP_DENORMALIZED;
            } else {
                return FFP_ZERO;
            }
        } else {
            return FFP_NORMALIZED;
        }
    }
}

/*
void test_fpclassf() {
    int psign;
    assert(fpclassf(+1.17549421069244107548702944484928734882705242874589e-38, &psign) == FFP_DENORMALIZED);
    assert(psign == 0);
    assert(fpclassf(-1.17549421069244107548702944484928734882705242874589e-38, &psign) == FFP_DENORMALIZED);
    assert(psign == 1);
    fprintf(stderr, "Denormalized -> OK\n");
    assert(fpclassf(+1.18e-38, &psign) == FFP_NORMALIZED);
    assert(psign == 0);
    assert(fpclassf(-1.18e-38, &psign) == FFP_NORMALIZED);
    assert(psign == 1);
    assert(fpclassf(1, &psign) == FFP_NORMALIZED);
    assert(psign == 0);
    assert(fpclassf(-1, &psign) == FFP_NORMALIZED);
    assert(psign == 1);
    assert(fpclassf(8.5070591730e+37, &psign) == FFP_NORMALIZED);
    assert(psign == 0);
    assert(fpclassf(-8.5070591730e+37, &psign) == FFP_NORMALIZED);
    assert(psign == 1);
    fprintf(stderr, "Normalized -> OK\n");
    assert(fpclassf(0.0, &psign) == FFP_ZERO);
    assert(psign == 0);
    assert(fpclassf(+0.0, &psign) == FFP_ZERO);
    assert(psign == 0);
    assert(fpclassf(-0.0, &psign) == FFP_ZERO);
    assert(psign == 1);
    assert(fpclassf(2.0 * 0, &psign) == FFP_ZERO);
    assert(psign == 0);
    assert(fpclassf(-2.0 * 0, &psign) == FFP_ZERO);
    assert(psign == 1);
    fprintf(stderr, "Zero -> OK\n");
    assert(fpclassf(1e+20 * 1e+20, &psign) == FFP_INF);
    assert(psign == 0);
    assert(fpclassf(-1e+20 * 1e+20, &psign) == FFP_INF);
    assert(psign == 1);
    union FU u;
    u.fvalue = sqrt(-1);
    assert(fpclassf(u.fvalue, &psign) == FFP_NAN);
    assert(psign == 0);
    fprintf(stderr, "NaN -> OK\n");
}

int main() {
    test_fpclassf();
}
*/

