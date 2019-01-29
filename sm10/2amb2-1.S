        .text
        .align  16
L1:     .asciz  "%llu\n"
        .global process
process:
        push    %ebp
        movl    %esp, %ebp
        push    %ebx

        // A == %edx:%eax, B == %ecx:%ebx
A_mult_2: 
        movl    A, %eax
        movl    A+4, %edx
        shl     %eax
        rcl     %edx
        
B_div_2: 
        movl    B, %ebx
        movl    B+4, %ecx
        shr     %ecx
        rcr     %ebx

A_sub_B:
        subl    %ebx, %eax
        sbbl    %ecx, %edx
 
print:  push    %edx
        push    %eax
        push    $L1
        call    printf
        add     $12, %esp

        pop     %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret

