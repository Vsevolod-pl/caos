#include <asm/unistd_32.h>

extern void writechar();
extern void flush();
extern struct FileWriteState *stout;
extern void writeu32();

void _start() {
    int ch = '\n';
    for (int i = 1; i != 10; ++i) {
        asm volatile(
            "movl %0, %%ecx\n"
            :: "g" (0)
            : "%ecx", "memory"
        );
        writeu32();
        asm volatile(
            "movl %0, %%ecx\n"
            "movl %1, %%edx\n"
            :: "g" (ch), "g" (stout)
            : "%ecx", "%edx", "memory"
        );
        writechar();
    }
    asm volatile(
        "movl %0, %%ecx\n"
        :: "g" (stout)
        : "%ecx", "memory"
    );
    flush();
    asm volatile(
        "mov %0, %%eax\n"
        "xor %%ebx, %%ebx\n"
        "int $0x80\n"
        :: "g" (__NR_exit)
        : "%eax", "%ebx", "memory"
    );
}

