#include <asm/unistd_32.h>

enum { BUFFER_SIZE = 4 * 1024 };

static unsigned char buffer[BUFFER_SIZE];

struct FileReadState {
    int fd;
    unsigned char *buf;
    int bufsize;
    int lc;
    int filled;
    int written;
};

static struct FileReadState state = {
    0, buffer, BUFFER_SIZE, -2, 0, 0
};

struct FileReadState *stin = &state;

int nextchar() {
    if (stin->lc == -1) {
        // No more read for ever!
        return -1;
    }
    int code = 0;
    if (stin->written == stin->filled) {
        if (stin->filled == stin->bufsize) {
            // Clean the buffer.
            stin->filled = stin->written = 0;
        }
        // Read bufsize - filled.
        asm volatile(
            "mov %1, %%eax\n"
            "mov %2, %%ebx\n"
            "mov %3, %%ecx\n"
            "mov %4, %%edx\n"
            "int $0x80\n"
            "mov %%eax, %0\n"
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
    return stin->lc;
}

int lastchar() {
    return stin->lc;
}

