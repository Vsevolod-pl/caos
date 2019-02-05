        .text
        .global dot_product
dot_product:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        subl    $12, %esp

        // 8(%ebp) == n == %eax
        // 12(%ebp) == *x == %ecx
        // 16(%ebp) == *y == %edx
        movl    8(%ebp), %eax
        movl    12(%ebp), %ecx
        movl    16(%ebp), %edx
        cmpl    $0, %eax
        je      empty

        xorps   %xmm0, %xmm0 
loop:   cmpl    $4, %eax
        jle     last
        // x -> %xmm1
        // y -> %xmm2
        // dot product -> %xmm0
        movupd  (%ecx), %xmm1
        addl    $16, %ecx
        movupd  (%edx), %xmm2
        addl    $16, %edx

mulp:   mulps   %xmm2, %xmm1
        haddps  %xmm2, %xmm1
        haddps  %xmm2, %xmm1
        addps   %xmm1, %xmm0
        cmpl    $4, %eax
        jle     return
        subl    $4, %eax
        jmp     loop

return: subl    $4, %esp
        movss   %xmm0, (%esp)
        flds    (%esp)
        addl    $4, %esp 

end:    addl    $12, %esp
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret

empty:  subl    $4, %esp
        movl    $0, (%esp)
        flds    (%esp)
        addl    $4, %esp
        jmp     end

last:   // Think of tail |4 - n|!
        subl    $16, %esp
        movl    $0, -28(%ebp)
        movl    $0, -24(%ebp)
        movl    $0, -20(%ebp)
        movl    $0, -16(%ebp)
        // -28, -24, -20, -16 (%ebp)
        movl    (%ecx), %esi
        movl    %esi, -28(%ebp)
        cmpl    $1, %eax
        je      lastmovx
        movl    4(%ecx), %esi
        movl    %esi, -24(%ebp)
        cmpl    $2, %eax
        je      lastmovx
        movl    8(%ecx), %esi
        movl    %esi, -20(%ebp)
        cmpl    $3, %eax
        je      lastmovx
        movl    12(%ecx), %esi
        movl    %esi, -16(%ebp) 
lastmovx:
        movupd  -28(%ebp), %xmm1

        movl    (%edx), %esi
        movl    %esi, -28(%ebp)
        cmpl    $1, %eax
        je      lastmovy
        movl    4(%edx), %esi
        movl    %esi, -24(%ebp)
        cmpl    $2, %eax
        je      lastmovy
        movl    8(%edx), %esi
        movl    %esi, -20(%ebp)
        cmpl    $3, %eax
        je      lastmovy
        movl    12(%edx), %esi
        movl    %esi, -16(%ebp) 
lastmovy:
        movupd  -28(%ebp), %xmm2
        addl    $16, %esp
        jmp     mulp

