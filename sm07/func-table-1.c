#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double(*funcptr_t)(double);
struct FunctionTable {
    const char *name;
    funcptr_t func;
};

static const struct FunctionTable table[] = {
    {"cos", cos},
    {"sin", sin},
    {"exp", exp},
    {"log", log},
    {"tan", tan},
    {"sqrt", sqrt},
};

int main() {
    char *func_name = NULL;
    double value;
    size_t i;
    size_t table_size = sizeof(table) / sizeof(table[0]);

    while (scanf("%ms%lf", &func_name, &value) == 2) {
        double result = NAN;
        for (i = 0; i < table_size; ++i) {
            if (!strcmp(table[i].name, func_name)) {
                result  = table[i].func(value);
                break;
            }
        }
        printf("%a\n", result);
        free(func_name);
        func_name = NULL;
    }

    return 0;
}

