        .data
        .global A, B, C
A:      .int    0
B:      .int    0
C:      .int    0
        .text
        .global process
process:
        push    %ebp
        mov     %esp, %ebp
        push    %ebx

        movl    A, %eax
        movl    X, %ecx
        mull    %ecx
        mull    %ecx
        mull    %ecx

        movl    %eax, %ebx

        movl    B, %eax
        mull    %ecx
        mull    %ecx
        movl    $2, %ecx
        mull    %ecx
        sub     %eax, %ebx
        addl    C, %ebx

        mov     %ebx, %eax

        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret
