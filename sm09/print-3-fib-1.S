        .text
        .global print_fib
L1:     .asciz  "%d %d %d\n"
        .align  16

print_fib:
        push    %ebp
        mov     %esp, %ebp

        mov     A, %eax
        addl    B, %eax
        movl    %eax, %ecx
        addl    B, %ecx
        movl    %ecx, %edx
        addl    %eax, %edx

        push    %edx
        push    %ecx
        push    %eax
        push    $L1
        call    printf

        add     $16, %esp

        popl    %ebp
        ret

