#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_ARGS_SIZE = 64 };

struct Data{
    uint32_t data[MAX_ARGS_SIZE / sizeof(uint32_t)];
};

union Double{
    double d;
    uint32_t i[2];
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

void *handle(
        void *handler,
        struct Data p_args,
        char return_type) {
    size_t result_size;
    if (return_type == 'd') {
        result_size = sizeof(double);
    } else if (return_type == 'i') {
        result_size = sizeof(int);
    } else {
        // return_type == 's'
        result_size = sizeof(char *);
    }
    void *p_result = malloc(result_size);
    if (!p_result) {
        return NULL;
    }
    // double : result at %st(0)
    // int : result at %eax
    // char * : result at %eax
    // void : do nothing
    if (return_type == 'i' || return_type == 's' || return_type == 'v') {
        // %ebx == counter 64->0
        // %ecx == p_args.data
        uint32_t result;
        asm volatile(
            "push %%ebp\n"
            "mov %%esp, %%ebp\n"
            "andl $0xFFFFFFF0, %%esp\n"
            "movl %2, %%ecx\n"
            "addl $64, %%ecx\n"
            "movl $64, %%ebx\n"
            "loop1:\n"
            "subl $4, %%ebx\n"
            "subl $4, %%ecx\n"
            "movl (%%ecx), %%eax\n"
            "push %%eax\n"
            "cmpl $0, %%ebx\n"
            "jne loop1\n"
            "call *%1\n"
            "mov %%eax, %0\n"
            "mov %%ebp, %%esp\n"
            "pop %%ebp\n"
            : "=g" (result)
            : "g"(handler), "g"(p_args.data)
            : "%eax", "%ebx", "%ecx", "%edx",
              "%ebp", "%esp", "%esi", "%edi",
              "memory"
        );
        /*
         *

            "push %%eax\n"
            "push %%ebx\n"
            "push %%ecx\n"
            "push %%edx\n"
            "movl $4, %%eax\n"
            "movl $2, %%ebx\n"
            "movl %3, %%ecx\n"
            "movl $1, %%edx\n"
            "int $0x80\n"
            "pop %%edx\n"
            "pop %%ecx\n"
            "pop %%ebx\n"
            "pop %%eax\n"



         */
        if (return_type == 'i' || return_type == 's') {
            *((uint32_t *)p_result) = result;
        }
    } else {
        // %ebx == counter 64->0
        // %ecx == p_args.data
        union Double result;
        asm volatile(
            "push %%ebp\n"
            "mov %%esp, %%ebp\n"
            "andl $-16, %%esp\n"
            "movl %2, %%ecx\n"
            "addl $64, %%ecx\n"
            "movl $64, %%ebx\n"
            "loop2:\n"
            "subl $4, %%ebx\n"
            "subl $4, %%ecx\n"
            "movl (%%ecx), %%eax\n"
            "push %%eax\n"
            "test %%ebx, %%ebx\n"
            "jne loop2\n"
            "call *%1\n"
            "subl $8, %%esp\n"
            "fstp (%%esp)\n"
            "pop %%eax\n"
            "mov %%eax, %0\n"
            "pop %%eax\n"
            "mov %%eax, %1\n"
            "addl $64, %%esp\n"
            "mov %%ebp, %%esp\n"
            "pop %%ebp\n"
            : "=g" (result.i[0]), "=g"(result.i[1])
            : "g"(handler), "g"(p_args.data)
            : "%eax", "%ebx", "%ecx", "%edx",
              "%ebp", "%esp", "%esi", "%edi",
              "memory"
        );
        *((double *)p_result) = result.d;
    }
    return p_result;
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
    void *result = handle(handler, p_args, return_type);
    if (return_type == 'd') {
        printf("%.10g\n", *(double *)result);
    } else if (return_type == 'i') {
        printf("%d\n", *(int *)result);
    } else if (return_type == 's') {
        printf("%s\n", *(char **)result);
    }
    dlclose(lib_handle);
    free(result);
    return 0;
}

