#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_ARGS_SIZE = 64 };

struct Data
{
    uint32_t data[MAX_ARGS_SIZE / sizeof(uint32_t)];
};

union Double
{
    double d;
    uint32_t i[2];
    struct
    {
        unsigned high : 32;
        unsigned low : 32;
    };
};

enum { SHIFT = 4 };

int parse_args(
        char **args,
        const char *signature,
        struct Data *data,
        char *return_type) {
    uint32_t num_args = 0;
    uint32_t *cursor = data->data;
    *return_type = *signature;
    while (*(++signature)) {
        if (*signature == 'i') {
            int item;
            if (sscanf(args[SHIFT + num_args++], "%d", &item) != 1) {
                fprintf(stderr, "Error while sscanf(%%d)\n");
                return 1;
            }
            *cursor = (uint32_t)item;
            ++cursor;
        } else if (*signature == 's') {
            *cursor = (uint32_t)args[SHIFT + num_args++];
            ++cursor;
        } else if (*signature == 'd') {
            union Double item;
            if (sscanf(args[SHIFT + num_args++], "%lf", &item.d) != 1) {
                fprintf(stderr, "Error while sscanf(%%lf)\n");
                return 1;
            }
            *cursor = item.i[0];
            ++cursor;
            *cursor = item.i[1];
            ++cursor;
        } else {
            // unknown type
            ++num_args;
        }
    }
    return 0;
}

typedef double (*d_function_)(struct Data);
typedef char * (*s_function_)(struct Data);
typedef int (*i_function_)(struct Data);
typedef void (*v_function_)(struct Data);

void handle(
        void *handler,
        struct Data p_args,
        char return_type) {
    if (return_type == 'd') {
        d_function_ f = (d_function_)handler;
        printf("%.10g\n", f(p_args));
    } else if (return_type == 'i') {
        i_function_ f = (i_function_)handler;
        printf("%d\n", f(p_args));
    } else if (return_type == 's') {
        s_function_ f = (s_function_)handler;
        printf("%s\n", f(p_args));
    } else {
        v_function_ f = (v_function_)handler;
        f(p_args);
    }
}

int main(int argc, char **argv) {
    const char *lib_name = argv[1];
    const char *handler_name = argv[2];
    const char *signature = argv[3];
    struct Data p_args;
    for (size_t i = 0; i != MAX_ARGS_SIZE / sizeof(uint32_t); ++i) {
        p_args.data[i] = 0U;
    }

    void *lib_handle = dlopen(lib_name, RTLD_NOW);
    if (!lib_handle) {
        fprintf(stderr, "Error while dlopen()");
        return 0;
    }
    void *handler = dlsym(lib_handle, handler_name);
    if (!handler) {
        fprintf(stderr, "Error while dlsym()\n");
        dlclose(lib_handle);
        return 0;
    }

    char return_type;
    int res = parse_args(argv, signature, &p_args, &return_type);
    if (res) {
        dlclose(lib_handle);
        return 0;
    }
    handle(handler, p_args, return_type);
    dlclose(lib_handle);
    return 0;
}

