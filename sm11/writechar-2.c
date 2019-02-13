#include <asm/unistd_32.h>

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

struct FileWriteState *stout;

enum { BUFFER_SIZE = 4 * 1024 };

// Когда вызывается:
// Пишем один символ в буфер.
// Далее: либо буфер полностью заполнен (filled == bufsize), тогда:
// вызываем flush
// Либо буфер заполнен не полностью (filled < bufsize), тогда:
// ничего не делаем

void __attribute__((fastcall)) writechar(int c, struct FileWriteState *out) {
    // %ecx <- c
    // %edx <- *out
    out->buffer[out->filled] = c;
    ++out->filled;
    if (out->filled == out->bufsize) {
        flush(out);
    } 
}

// делаем write на заполненную часть буфера (смотрим на filled)
// ставим filled = 0

// Если не так всё просто...

void __attribute__((fastcall)) flush(struct FileWriteState *out) {
    // %ecx <- *out
    // 0(%ecx) <- out.fd
    // 4(%ecx) <- out.buf
    asm volatile(
        "mov %1, %%eax\n"
        "mov %2, %%ebx\n"
        "leal 4(%%ecx), %%ecx"
        "mov %3, %%edx\n"
        "int $0x80\n"
        "mov %%eax, %0\n"
        : "=g" (code)
        : "g" (__NR_write), "g" (1), "g" (out->filled)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    out->filled = 0;
}

// А возможно так просто?

void __attribute__((fastcall)) flush(struct FileWriteState *out) {
    // %ecx <- *out
    // 0(%ecx) <- out.fd
    // 4(%ecx) <- out.buf
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

void flush(struct FileWriteState *out) {

}

