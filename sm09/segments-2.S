        .text
        .align  16
Lscan:  .asciz  "%d%d%d%d"
Lprint: .asciz  "%d\n"

        .global process
process:
        push    %ebp
        mov     %esp, %ebp
        // %ebx -- sum of segments
        push    %ebx
        xor     %ebx, %ebx
 
        subl    $16, %esp

loop:   lea     -8(%ebp), %eax
        push    %eax
        lea     -12(%ebp), %eax
        push    %eax
        lea     -16(%ebp), %eax
        push    %eax
        lea     -20(%ebp), %eax
        push    %eax
        push    $Lscan

        call    scanf
        addl    $4, %esp
        addl    $16, %esp
        cmpl    $4, %eax
        jne     print

        /*
            a1 -> -20(%ebp)
            b1 -> -16(%ebp)
            a2 -> -12(%ebp)
            b2 -> -8(%ebp)
        */
        movl    -12(%ebp), %eax
        cmpl    -16(%ebp), %eax
        jge     loop
        movl    -20(%ebp), %eax
        cmpl    -8(%ebp), %eax
        jge     loop


        // %eax == left, %edx == right
        movl    -20(%ebp), %eax
        cmpl    -12(%ebp), %eax
        cmovl   -12(%ebp), %eax

        movl    -16(%ebp), %edx
        cmpl    -8(%ebp), %edx
        cmovg   -8(%ebp), %edx

        sub     %eax, %edx
        addl    %edx, %ebx

        jmp     loop

print:
        subl    $12, %esp
        push    %ebx
        push    $Lprint

        call    printf
        addl    $20, %esp
epilogue:
        addl    $16, %esp
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret

