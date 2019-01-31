        .global myhypot
myhypot:
        push    %ebp
        mov     %esp, %ebp
        /*
                8(%ebp) -> x
                16(%ebp) -> y
                24(%ebp) -> *r
                (24(%ebp)) -> r
        */
        movsd   8(%ebp), %xmm0
        movl    16(%ebp), %eax
        movl    20(%ebp), %edx
        push    %edx
        push    %eax
        movsd   -8(%ebp), %xmm1
        mulsd   %xmm0, %xmm0
        mulsd   %xmm1, %xmm1
        addsd   %xmm1, %xmm0
        sqrtsd  %xmm0, %xmm0

        
        mov     24(%ebp), %eax
        movsd   %xmm0, (%eax)

end:
        addl    $8, %esp
        mov     %ebp, %esp
        pop     %ebp
        ret

