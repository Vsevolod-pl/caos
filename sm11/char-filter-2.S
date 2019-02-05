#include <asm/unistd_32.h>
        .text
char_a: .byte  'a'
char_z: .byte  'z'
char_A: .byte  'A'

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

        cmpl    $0, %eax
        je      end

        movb    (%esp), %ecx
        cmpb    char_a, %ecx
        jl      print
        cmpb    char_z, %ecx
        jg      print
        addb    char_A, %ecx
        subb    char_a, %ecx

print:  movb    %ecx, (%esp)
        mov     $__NR_write, %eax
        mov     $1, %ebx
        mov     %esp, %ecx
        mov     $1, %edx
        int     $0x80
        jmp     loop

end:
        mov     $__NR_exit, %eax
        xor     %ebx, %ebx
        int     $0x80
