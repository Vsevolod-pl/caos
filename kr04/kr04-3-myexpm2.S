        .text
        .align  16
l0:     .double 0.0
        .align  16
l1:     .double 1.0
        .align  16
lneg:   .double -1.0
        .global myexpm2
myexpm2:
        // 8(%ebp) 
        // 16(%ebp)
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi
        push    %ebx

        andl    $0xfffffff0, %esp

        movsd   l0, %xmm0
        movsd   l0, %xmm1
        movsd   8(%ebp), %xmm2 
        mulsd   %xmm2, %xmm2
        movsd   l1, %xmm3
        movsd   l0, %xmm4
        movsd   lneg, %xmm5

loop:   
        addsd   %xmm3, %xmm1
        comisd  %xmm1, %xmm0
        jz      return
        movsd   %xmm1, %xmm0
        mulsd   %xmm2, %xmm3
        addsd   l1, %xmm4
        divsd   %xmm4, %xmm3
        mulsd   %xmm5, %xmm3
        jmp     loop
        

return: movl    16(%ebp), %esi
        sub     $8, %esp
        movsd   %xmm0, (%esp)

        movl    0(%esp), %eax
        movl    %eax, 0(%esi)

        movl    4(%esp), %eax
        movl    %eax, 4(%esi)
        
        add     $8, %esp

end:    mov     %ebp, %esp
        subl    $12, %esp
        pop     %ebx
        pop     %edi
        pop     %esi
        pop     %ebp
        ret

