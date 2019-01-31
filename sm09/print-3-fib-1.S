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

        // Trash to 16-align.
        subl    $8, %esp

        push    %edx
        push    %ecx
        push    %eax
        push    $L1
        call    printf

        add     $24, %esp

        popl    %ebp
        ret

