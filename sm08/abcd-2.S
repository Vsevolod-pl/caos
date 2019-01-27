        .data
        .global A, B, C, D, R
A:      .int    0
B:      .int    0
C:      .int    0
D:      .int    0
R:      .int    0


        .text
        .global process
        mov     A, B
        add     C, D
process:
        mov     C, %ebx
label1: mov     D, %eax
        imull   %ebx
        movl    %eax, %esi

        mov     A, %ebx
        mov     B, %eax
        imull   %ebx
        subl    %esi, %eax
        mov     %eax, R
        ret

