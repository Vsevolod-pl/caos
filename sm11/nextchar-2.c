#include <asm/unistd_32.h>

static unsigned char buffer[10000];

struct FileReadState {
    int fd;
    unsigned char *buf;
    int bufsize;
    int lc;
    int filled;
    int written;
};

enum { BUFFER_SIZE = 4 * 1024 };

struct FileReadState state = {
    0, buffer, BUFFER_SIZE, -2, 0, 0
};

struct FileReadState *stin = &state;

void write_debug(char ch) {
    int code;
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

int nextchar() {
    if (stin->lc == -1) {
        write_debug('e');
        // No more read for ever!
        return -1;
    }
    int code = 0;
    if (stin->written == stin->filled) {
        write_debug('=');
        if (stin->filled == stin->bufsize) {
            // Clean the buffer.
            stin->filled = stin->written = 0;
        }
        // Read bufsize - filled.
        asm volatile(
            "\n"
            : "=g"(code)
            : "g" (__NR_read), "g" (0), "g" (stin->buf + stin->filled), "g" (stin->bufsize - stin->filled)
            : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
        if (code <= 0) {
            // Return only -1 from now.
            stin->lc = -1;
            return stin->lc;
        } else {
            stin->filled += code;
        }
    }
    stin->lc = stin->buf[stin->written];
    ++(stin->written);
    write_debug('h');
    return stin->lc;
}

int lastchar() {
    return stin->lc;
}

void _start() {
    int ch;
    int code;
    for (int i = 0; i != 2; ++i) {
    // while ((ch = nextchar()) != -1) {
    
        ch = nextchar();
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
        /*
        asm volatile(
            "mov %1, %%eax\n"
            "mov %2, %%ebx\n"
            "mov %3, %%ecx\n"
            "mov %4, %%edx\n"
            "int $0x80\n"
            "mov %%eax, %0\n"
            : "=g" (code)
            : "g" (__NR_write), "g" (2), "g" (&ch), "g" (1)
            : "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
        */
    }
    asm volatile(
        "mov %0, %%eax\n"
        "xor %%ebx, %%ebx\n"
        :
        : "g" (__NR_exit)
        : "%eax", "%ebx", "memory"
    );
}

