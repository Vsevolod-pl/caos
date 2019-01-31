        .text
        .global dot_product
dot_product:
        push    %ebp
        mov     %esp, %ebp
        subl    $12, %esp

        // -28(%ebp) -- 128bit start
        subl    $16, %esp

        // DEBUG
        movl    %esp, %eax
        call    writei32
        call    nl
        // DEBUG

        /*
         8(%ebp) == n  -> %eax
        12(%ebp) == *x -> %ecx
        16(%ebp) == *y -> %edx
        */
        movl    8(%ebp), %eax
        movl    12(%ebp), %ecx
        movl    16(%ebp), %edx


loop:
        movl    $0, -28(-%ebp)
        movl    $0, -24(-%ebp)
        movl    $0, -20(-%ebp)
        movl    $0, -16(-%ebp)

        
        /*
        x -> %xmm1
        y -> %xmm2
        dot product -> %xmm0
        */


return:
        subl    $4, %esp
        movss   %xmm0, (%esp)
        flds    (%esp)
        addl    $4, %esp
        
end:
        // DEBUG
        movl    %esp, %eax
        call    writei32
        call    nl
        // DEBUG

        addl    $12, %esp
        mov     %ebp, %esp
        pop     %ebp
        ret
