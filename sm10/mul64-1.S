        .text
        .align  16
print2: .asciz  "%llx%016llx\n"
        .align  16
print1: .asciz  "%llx\n"

        .text
        .global mul64p
mul64p:
        push    %ebp
        mov     %esp, %ebp
        subl    $28, %esp
        // 8.12(%ebp) == xb.xa
        // 16.20(%ebp) == yd.yc

        // -8.-4(%ebp) == -24.-20(%ebp) == H
        // -16.-12(%ebp) == L
        movl    $0, -16(%ebp)
        movl    $0, -12(%ebp)
        movl    $0, -8(%ebp)
        movl    $0, -4(%ebp)

        // xb * yd -> -16.-12
        movl    8(%ebp), %eax
        mull    16(%ebp)
        mov     %eax, -16(%ebp)
        mov     %edx, -12(%ebp)
        // xa * yd -> -12.-8
        movl    12(%ebp), %eax
        mull    16(%ebp)
        addl    %eax, -12(%ebp)
        adcl    %edx, -8(%ebp)
        // xb * yc -> -12.-8
        movl    8(%ebp), %eax
        mull    20(%ebp)
        addl    %eax, -12(%ebp)
        adcl    %edx, -8(%ebp)
        adcl    $0, -4(%ebp)
        // xa * yc -> -8.-4
        movl    12(%ebp), %eax
        mull    20(%ebp)
        addl    %eax, -8(%ebp)
        adcl    %edx, -4(%ebp)

        // Check for leading zero-64-bit.
        cmpl    $0, -8(%ebp)
        jne     print_two
        cmpl    $0, -4(%ebp)
        jne     print_two

print_one:
        movl    -16(%ebp), %eax
        movl    %eax, -24(%ebp)
        movl    -12(%ebp), %eax
        movl    %eax, -20(%ebp)
        movl    $print1, -28(%ebp)
        call    printf

end:    addl    $28, %esp
        mov     %ebp, %esp
        pop     %ebp
        ret

print_two:
        movl    -8(%ebp), %eax
        movl    %eax, -24(%ebp)
        movl    -4(%ebp), %eax
        movl    %eax, -20(%ebp)
        movl    $print2, -28(%ebp)
        call    printf
        jmp     end

