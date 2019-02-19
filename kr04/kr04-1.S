        .text
        .global forward.args
forward.args:
        // 8: v1, 4: v2, 4: v3
        push    %ebp
        mov     %esp, %ebp
        // 8(%ebp) == v1
        // 16(%ebp) == v2
        // 20(%ebp) == v3
        push    %esi
        push    %ebx
        subl    $16, %esp
        
        movl    8(%ebp), %eax
        movl    %eax, -12(%ebp)
        
        // OK
        movl    20(%ebp), %eax
        movl    %eax, -24(%ebp)

        movl    16(%ebp), %eax
        cdq
        movl    %eax, -20(%ebp)
        movl    %edx, -16(%ebp)
        call    process

        negl    %eax

        addl    $16, %esp
        pop     %ebx
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret
