#include <asm/unistd_32.h>

enum { BUFFER_SIZE = 4 * 1024 };

static unsigned char buffer[BUFFER_SIZE];

struct FileWriteState
{
    int fd;
    unsigned char *buf;
    int bufsize;
    int filled;
};

struct FileWriteState state = {
    1, buffer, BUFFER_SIZE, 0
};

struct FileWriteState *stout = &state;

void __attribute__((fastcall)) flush() {
    struct FileWriteState *out;
    int code;
    asm volatile(
        "mov %%ecx, %0\n"
        : "=g" (out)
        :: "%ecx", "memory"
    );
    asm volatile(
        "mov %1, %%eax\n"
        "mov %2, %%ebx\n"
        "mov %3, %%ecx\n"
        "mov %4, %%edx\n"
        "int $0x80\n"
        "mov %%eax, %0\n"
        : "=g" (code)
        : "g" (__NR_write), "g" (1), "g" (out->buf), "g" (out->filled)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    out->filled = 0;
}

void __attribute__((fastcall)) writechar() {
    int c;
    struct FileWriteState *out;
    asm volatile(
        "movl %%ecx, %0\n"
        "movl %%edx, %1\n"
        : "=g" (c), "=g" (out)
        :: "memory"
    );
    if (out->filled == out->bufsize) {
        asm volatile(
            "mov %0, %%ecx"
            :: "g" (out)
            : "%ecx", "memory"
        );
        flush();
    }
    out->buf[out->filled] = c;
    ++out->filled;
    if (out->filled == out->bufsize) {
        asm volatile(
            "mov %0, %%ecx"
            :: "g" (out)
            : "%ecx", "memory"
        );
        flush();
    } 
}

