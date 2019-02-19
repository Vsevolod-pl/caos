        .text
        .global addbe
addbe:
        // 8(%ebp) == n
        // 12(%ebp) == *pa
        // 16(%ebp) == *pb
        // 20(%ebp) == *pc
        push    %ebp
        mov     %esp, %ebp
        push    %ebx
        push    %esi
        push    %edi
    
        // %ebx == i
        // %esi == carry
        movl    8(%ebp), %ebx
        // Clear carry, clear carry flag
        xor     %esi, %esi
loop:   
        // --i
        decl    %ebx

        // %eax = pa[i]
        movl    12(%ebp), %ecx
        xor     %eax, %eax
        xor     %edx, %edx
        movb    0(%ecx, %ebx, 1), %eax

        // %eax += pb[i] + carry
        movl    16(%ebp), %ecx
        movb    0(%ecx, %ebx, 1), %edx
        addl    %edx, %eax
        addl    %esi, %eax
        xor     %esi, %esi
        cmpl    $0xff, %eax
        jbe     put
        movl    $1, %esi

put:    // pc[i] = %eax
        movl    20(%ebp), %ecx
        movb    %eax, 0(%ecx, %ebx, 1)

        // carry = CF
        test    %ebx, %ebx
        jne     loop

        test    %esi, %esi
        jnz     unsigned_overflow
        // Return 0.
        xor     %eax, %eax
end:    
        pop     %edi
        pop     %esi
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret

unsigned_overflow:
        movl    $1, %eax
        jmp     end

