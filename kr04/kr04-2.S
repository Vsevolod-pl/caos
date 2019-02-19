        .text
        .global process
process:
        // 8(%ebp) == *p
        // 0(8(%ebp)) == U
        // 4(8(%ebp)) == V
        // 8, 12, 16, 20(8(%ebp)) == W
        // 24(8(%ebp)) == X

        // 12(%ebp) == i
        push    %ebp
        mov     %esp, %ebp
        push    %ebx
        push    %esi
        push    %edi  // -12(%ebp)
        subl    $8, %esp

        // %ebx = *p
        movl    8(%ebp), %ebx  // *p
        // %edi = i
        movl    12(%ebp), %edi  // i
        // %eax = U
        movl    0(%ebx), %eax
        // %esi = W + i * 4
        movl    8(%ebx, %edi, 4), %esi
        // %eax *= %esi
        mull    %esi
        movl    %edx, -16(%ebp)
        movl    %eax, -20(%ebp)

        // %eax = V
        movl    4(%ebx), %eax
        // %esi = X
        movl    24(%ebx), %esi
        imull   %esi

        // (edx:eax) + (esi:edi)
        movl    -16(%ebp), %esi
        movl    -20(%ebp), %edi
        add     %eax, %edi
        adc     %edx, %esi
        jo      overflow
        movl    %esi, %edx
        movl    %edi, %eax

end:    addl    $8, %esp
        pop     %edi
        pop     %esi
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret
        
overflow:
        // Return -1.
        movl    $0xffffffff, %eax
        movl    $0xffffffff, %edx
        jmp     end


