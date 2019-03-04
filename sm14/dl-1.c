#include <dlfcn.h>
#include <stdio.h>

typedef double (*math_func)(double);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough argv\n");
        return 1;
    }
    const char MATH_LIB_NAME[] = "/lib/libm.so.6";
    void *handle = dlopen(MATH_LIB_NAME, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Error while dlopen()\n");
        return 1;
    }
    void *sym = dlsym(handle, argv[1]);
    if (!sym) {
        fprintf(stderr, "Error while dlsym()\n");
        dlclose(handle);
        return 1;
    }
    math_func f = sym;
    double x;
    while (scanf("%lf", &x) == 1) {
        printf("%.10g\n", f(x));
    }
    dlclose(handle);
    return 0;
}

