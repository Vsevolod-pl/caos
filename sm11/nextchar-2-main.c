#include <asm/unistd_32.h>

extern int nextchar();
extern int lastchar();
extern struct FileReadState *stin;

void _start() {
    int ch;
    int code;
    while ((ch = nextchar()) != -1) { 
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
        int ch1 = lastchar(), ch2 = lastchar(), ch3 = lastchar();
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch1), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch2), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        ); 
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch3), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        ); 
    }
        int ch1 = nextchar(), ch2 = nextchar(), ch3 = nextchar();
        if (ch1 == -1) {
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch1), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
        }
        if (ch2 == -1) {
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch2), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        ); 
        }
        if (ch3 == -1) {
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch3), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        ); 
        }
        ch1 = lastchar(), ch2 = lastchar(), ch3 = lastchar();
        if (ch1 == -1) {
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch1), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
        }
        if (ch2 == -1) {
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch2), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        ); 
        }
        if (ch3 == -1) {
        asm volatile(
                "mov %1, %%eax\n"
                "mov %2, %%ebx\n"
                "mov %3, %%ecx\n"
                "mov %4, %%edx\n"
                "int $0x80\n"
                "mov %%eax, %0\n"
                : "=g" (code)
                : "g" (__NR_write), "g" (2), "g" (&ch3), "g" (1)
                : "%eax", "%ebx", "%ecx", "%edx", "memory"
        ); 
        }
    asm volatile(
        "mov %0, %%eax\n"
        "xor %%ebx, %%ebx\n"
        "int $0x80\n"
        :
        : "g" (__NR_exit)
        : "%eax", "%ebx", "memory"
    );
}
