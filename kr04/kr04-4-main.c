#include <assert.h>
#include <stdio.h>
#include <string.h>

extern int addbe(size_t n, const unsigned char *pa, const unsigned char *pb, unsigned char *pc);

void print_long_number(size_t n, const unsigned char *in) {
    for (int i = 0; i != n; ++i) {
        fprintf(stderr, "|%02x", *(in + i));
    }
}

void check(
        int n, 
        const unsigned char *pa, const unsigned char *pb, unsigned char *out,
        int result, const unsigned char *ref) {
    fprintf(stderr, "<----------------->\nTest :\n");
    fprintf(stderr, " ");
    print_long_number(n, pa);
    fprintf(stderr, "\n+\n");
    fprintf(stderr, " ");
    print_long_number(n, pb);
    fprintf(stderr, "\n-");
    for (int i = 0; i != n; ++i) {
        fprintf(stderr, "---");
    }
    fprintf(stderr, "-\n");
    fprintf(stderr, "%d", result);
    print_long_number(n, ref);
    fprintf(stderr, "\n");
    fprintf(stderr, "Your result is:\n");
    int out_result = addbe(n, pa, pb, out);
    fprintf(stderr, "%d", out_result);
    print_long_number(n, out);
    fprintf(stderr, "\n");
    assert(out_result == result);
    fprintf(stderr, "return is OK\n");
    for (int i = 0; i != n; ++i) {
        assert(*(out + i) == *(ref + i));
    }
    fprintf(stderr, "sum is OK\n");
    fprintf(stderr, "test is OK\n");
}

int main() {
    unsigned char a[8];
    unsigned char b[8];
    unsigned char out[8];
    unsigned char ref[8];
    memcpy(a, (unsigned char[6]){ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x42 }, sizeof(unsigned char[6]));
    memcpy(b, (unsigned char[6]){ 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x66 }, sizeof(unsigned char[6]));

    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[2]){ 0x00, 0xFE }, sizeof(unsigned char[2]));
    check(2, a, b, out, 1, ref);

    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[6]){ 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0xA8 }, sizeof(unsigned char[6]));
    check(6, a, b, out, 1, ref);

    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[1]){ 0xFF }, sizeof(unsigned char[1]));
    check(1, a, b, out, 0, ref);


    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[3]){ 0x00, 0xFF, 0xFE}, sizeof(unsigned char[3]));
    check(3, a, b, out, 1, ref);

    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[4]){ 0x00, 0xFF, 0xFF, 0xFE }, sizeof(unsigned char[4]));
    check(4, a, b, out, 1, ref);

    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[5]){ 0x00, 0xFF, 0xFF, 0xFF, 0xFE }, sizeof(unsigned char[5]));
    check(5, a, b, out, 1, ref);


    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(a, (unsigned char[8]){ 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF}, sizeof(unsigned char[8]));
    memcpy(b, (unsigned char[8]){ 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01}, sizeof(unsigned char[8]));

    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[1]){ 0x35 }, sizeof(unsigned char[1]));
    check(1, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[2]){ 0x35, 0x79 }, sizeof(unsigned char[2]));
    check(2, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[3]){ 0x35, 0x79, 0xBD }, sizeof(unsigned char[3]));
    check(3, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[4]){ 0x35, 0x79, 0xBE, 0x01 }, sizeof(unsigned char[4]));
    check(4, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[5]){ 0x35, 0x79, 0xBE, 0x02, 0x45 }, sizeof(unsigned char[5]));
    check(5, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[6]){ 0x35, 0x79, 0xBE, 0x02, 0x46, 0x89 }, sizeof(unsigned char[6]));
    check(6, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[7]){ 0x35, 0x79, 0xBE, 0x02, 0x46, 0x8A, 0xCD }, sizeof(unsigned char[7]));
    check(7, a, b, out, 0, ref);
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[8]){ 0x35, 0x79, 0xBE, 0x02, 0x46, 0x8A, 0xCE, 0x00 }, sizeof(unsigned char[8]));
    check(8, a, b, out, 0, ref);


    // Sample
    memcpy(a, (unsigned char[2]){ 0x25, 0x6C }, sizeof(unsigned char[2]));
    memcpy(b, (unsigned char[2]){ 0x00, 0xA5 }, sizeof(unsigned char[2]));
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[2]){ 0x26, 0x11 }, sizeof(unsigned char[2]));
    check(2, a, b, out, 0, ref);
    
    memcpy(a, (unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0 }, sizeof(unsigned char[8]));
    memcpy(b, (unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0 }, sizeof(unsigned char[8]));
    memcpy(out,(unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0}, sizeof(unsigned char[8]));
    memcpy(ref, (unsigned char[8]){ 0, 0, 0, 0, 0, 0, 0, 0 }, sizeof(unsigned char[8]));
    check(1, a, b, out, 0, ref);
    check(2, a, b, out, 0, ref);
    check(3, a, b, out, 0, ref);
    check(4, a, b, out, 0, ref);
    check(5, a, b, out, 0, ref);
    check(6, a, b, out, 0, ref);
    check(7, a, b, out, 0, ref);
    check(8, a, b, out, 0, ref);
    return 0;
}

