#include <asm/unistd_32.h>

void _start() {
    char ch = 0;
    int code = 0;
    while (42) {
        asm volatile(
            "mov %1, %%eax\n"
            "mov %2, %%ebx\n"
            "mov %3, %%ecx\n"
            "movl $0, (%%ecx)\n"
            "mov %4, %%edx\n"
            "int $0x80\n"
            "movl %%eax, %0\n"
            : "=g" (code)
            : "g" (__NR_read), "g" (0), "g" (&ch), "g" (1)
            : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
        if (code == 0) {
            break;
        }
        if (ch >= 'a' && ch <= 'z') {
            ch += 'A' - 'a';
        }
        asm volatile(
            "mov %1, %%eax\n"
            "mov %2, %%ebx\n"
            "mov %3, %%ecx\n"
            "mov %4, %%edx\n"
            "int $0x80\n"
            "mov %%eax, %0\n"
            : "=g" (code)
            : "g" (__NR_write), "g" (1), "g" (&ch), "g" (1)
            : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
    }
    asm volatile(
        "mov %0, %%eax\n"
        "xor %%ebx, %%ebx\n"
        "int $0x80"
        : 
        : "g" (__NR_exit)
        : "%eax", "%ebx", "memory"
    );
}

