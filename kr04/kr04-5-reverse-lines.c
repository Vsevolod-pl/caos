#include <stdio.h>
#include <unistd.h>
#include <asm/unistd_32.h>

int my_read(int in_fd, unsigned char *out, int size) {
    int errcode = 0;
    asm volatile(
        "mov %1, %%eax\n"
        "mov %2, %%ebx\n"
        "mov %3, %%ecx\n"
        "mov %4, %%edx\n"
        "int $0x80\n"
        "mov %%eax, %0\n"
        : "=g" (errcode)
        : "g" (__NR_read), "g" (in_fd), "g" (out), "g" (size)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    return errcode;
    // return read(in_fd, out, size);
}

void my_exit(int exitcode) {
    asm volatile(
        "mov %0, %%eax\n"
        "movl %1, %%ebx\n"
        "int $0x80\n"
        :: "g" (__NR_exit), "g" (exitcode)
        : "%eax", "%ebx"
    );
}


/*
void write_data(int out_fd, void *data, int data_size) {
    unsigned char buf[BUF_SIZE];
    ssize_t err_code;
    while ((err_code = my_read()) > 0) {
    }
    if (*(data + data_size - 1) != '\n') {
        char nl = '\n';
        my_write(out_fd, &nl, 1);
    }
}
*/

enum { BUF_SIZE = 4096 };

void *my_brk(void *newbrk) {
    void *result = NULL;
    asm volatile(
        "movl %1, %%eax\n"
        "movl %2, %%ebx\n"
        "int $0x80\n"
        "movl %%eax, %0\n"
        : "=g" (result)
        : "g" (__NR_brk), "g" (newbrk)
        : "%eax", "%ebx", "memory"
    );
    return result;
}

int read_data(int in_fd, unsigned char **pdata) {
    unsigned char *data = (unsigned char *)my_brk(NULL);
    ssize_t num_read;
    unsigned char *new_data = NULL;
    int current_size = 0;
    do {
        new_data = (unsigned char *)my_brk(data + current_size + BUF_SIZE);
        current_size += BUF_SIZE;
        num_read = my_read(in_fd, data + current_size - BUF_SIZE, BUF_SIZE);
        if (num_read > 0) {
            current_size += num_read - BUF_SIZE;
            new_data = (unsigned char *)my_brk(data + current_size);
        } else {
            if (num_read == 0) {
                current_size -= BUF_SIZE;
                if (*(data + current_size - 1) != '\n') {
                    new_data = (unsigned char *)my_brk(data + current_size + 1);
                    *(data + current_size) = '\n';
                    ++current_size;
                }
            } else {
                // num_read == -1
                // abort();
            }
            break;
        }
    } while (42);
    *pdata = data;
    return current_size;
}

void start() {
    unsigned char *data = NULL;
    // 0 == stdin
    int data_size = read_data(0, &data);
    fprintf(stderr, "data_size == %d\n", data_size);
    fprintf(stderr, "%c\n", data[10]);
    for (int i = 0; i != data_size; ++i) {
        fprintf(stderr, "%c", data[i]);
    }
    fprintf(stderr);
    // 1 == stdout
    // write_data(1, data, data_size);
    data = (unsigned char *)my_brk(data);
    fprintf(stderr, "data == %p\n", data);
    my_exit(0);
}

int main() {
    start();
    return 0;
}
