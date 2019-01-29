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
 
        sub     $16, %esp

loop:   lea     12(%esp), %eax
        push    %eax
        lea     12(%esp), %eax
        push    %eax
        lea     12(%esp), %eax
        push    %eax
        lea     12(%esp), %eax
        push    %eax
        push    $Lscan
        call    scanf
        add     $4, %esp
        add     $16, %esp
        jmp     print_debug
continue:
        cmpl    $4, %eax
        jne     print

        /*
            a1 -> 0(%esp)
            b1 -> 4(%esp)
            a2 -> 8(%esp)
            b2 -> 12(%esp)
        */
        movl    8(%esp), %eax
        cmpl    4(%esp), %eax
        jge     loop
        movl    0(%esp), %eax
        cmpl    12(%esp), %eax
        jge     loop


        // %eax == left, %edx == right
        movl    0(%esp), %eax
        cmpl    8(%esp), %eax
        cmovl   8(%esp), %eax

        movl    4(%esp), %edx
        cmpl    12(%esp), %edx
        cmovg   12(%esp), %edx

        sub     %eax, %edx
        addl    %edx, %ebx

        jmp     loop

print:
        push    %ebx
        push    $Lprint
        call    printf
        add     $8, %esp
epilogue:
        add     $16, %esp
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret


print_debug:
/*
        call    writei32
        call    nl
        movl    0(%esp), %eax
        call    writei32
        call    nl
        movl    4(%esp), %eax
        call    writei32
        call    nl
        movl    8(%esp), %eax
        call    writei32
        call    nl
        movl    12(%esp), %eax
        call    writei32
        call    nl
        call    nl
*/
        jmp     continue

