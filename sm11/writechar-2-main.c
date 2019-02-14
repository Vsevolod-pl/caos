#include <asm/unistd_32.h>

extern void writechar();
extern void flush();
extern struct FileWriteState *stout;
extern int nextchar();
extern int lastchar();
extern struct FileReadState *stin;

void _start() {
    int ch;
    while ((ch = nextchar()) != -1) {
        asm volatile(
            "movl %0, %%ecx\n"
            "movl %1, %%edx\n"
            :: "g" (ch), "g" (stout)
            : "%ecx", "%edx", "memory"
        );
        writechar();
    }
    asm volatile(
        "movl %0, %%ecx"
        :: "g" (stout)
        : "%ecx", "memory"
    );
    flush();
    asm volatile(
        "mov %0, %%eax\n"
        "xor %%ebx, %%ebx\n"
        "int $0x80\n"
        :
        : "g" (__NR_exit)
        : "%eax", "%ebx", "memory"
    );
}

