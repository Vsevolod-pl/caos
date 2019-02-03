#include <asm/unistd_32.h>
        .text
int0:   .byte  '0'
int9:   .byte  '9'

        .text
        .global _start
_start:
        push    %ebp
        mov     %esp, %ebp
        andl    $0xFFFFFFF0, %esp
        subl    $16, %esp

loop:   mov     $__NR_read, %eax
        mov     $0, %ebx
        mov     %esp, %ecx
        movl    $0, (%esp)
        mov     $1, %edx
        int     $0x80

        #       no more read
        cmpl    $0, %eax
        je      end

        movb    (%esp), %ecx
        cmpb    int0, %ecx
        jl      print
        cmpb    int9, %ecx
        jg      print
        movb    int0, %ecx

print:  movb    %ecx, (%esp)
        mov     $__NR_write, %eax
        mov     $1, %ebx
        mov     %esp, %ecx
        mov     $1, %edx
        int     $0x80
        jmp     loop

end:
        mov     $__NR_exit, %eax
        mov     $1, %ebx
        int     $0x80
