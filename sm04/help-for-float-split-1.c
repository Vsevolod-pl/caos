#include <stdint.h>
#include <stdio.h>

// floats have only comparisons and casts :(
int main() {
    float x;
    uint32_t ux;
    if (scanf("%f", &x) == 1) {
        // DEFINITELY NOT ux = x cause bit representation changes
        // ux = * (uint32_t *) &x; could be! but don't do it
        // because it's not safe (possibly different offset rules
        // so we got undefined behavior)

        // float* pf, unsigned* pl:
        // strict aliasing rule! different type pointers don't refer to same memory location
        // (except void*, unsigned/signed char*)

        // Option 1.
        numcpy(&ux, &x, sizeof(ux));
        // Pretend we're interested in a == yyyyxxxxxxyyyyyyy's x-bits (7..12th bits):
        //                                  65432109876543210
        (a >> 7) & 0x1F
        0b111111 = (1U << 6) - 1;
    }

    return 0;
}

// Option 2:
union FU {  // fv and uv refer to same memory location! That's what union exist for
    float fv;
    uin32_t uv;
};

// Option 3:
Union FU {
    float fv;
    struct {
        unsigned s:1;
        unsigned p:8;
        unsigned m:23;
    }
};

FU u;
// so get u.s if it works (if anonymous structs work. if they ain't give a name to the structure)
// check if bit order is s, p, m indeed.
