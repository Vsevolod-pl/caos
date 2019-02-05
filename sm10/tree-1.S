        .text
        .align  16
eps:    .double 1e-8
        .align  16
sign:   .quad   0x7fffffffffffffff

        .align  16
        .global tree_find
tree_find:
        push    %ebp
        mov     %esp, %ebp

        //  8(%ebp) == *root == %eax
        // 12(%ebp) == key   == %xmm0
        // 20(%ebp) == **pstr

        // Check for null root.
        movl    8(%ebp), %eax
        test    %eax, %eax
        je      nfound

        // key    ==   0(%eax)
        // *left  ==   8(%eax)
        // *right ==  12(%eax)
        // *str   ==  16(%eax)
        movsd   12(%ebp), %xmm0
        movsd   sign, %xmm3
compare:
        // key  -> %xmm0
        // item -> %xmm1, %xmm2
        // sign -> %xmm3
        movsd   0(%eax), %xmm1
        movsd   0(%eax), %xmm2
        subsd   %xmm0, %xmm1
        andpd   %xmm3, %xmm1
        comisd  eps, %xmm1
        jbe     found
ne:     comisd  %xmm0, %xmm2
        ja      to_left
        jb      to_right

to_left:
        mov     8(%eax), %eax
        test    %eax, %eax
        jz      nfound
        jmp     compare
to_right:
        mov     12(%eax), %eax
        test    %eax, %eax
        jz      nfound
        jmp     compare

found:  mov     20(%ebp), %ecx  // ecx = **pstr
        // Check for null pstr.
        test    %ecx, %ecx
        jz      null_pstr
        mov     16(%eax), %edx  // edx = *str
        mov     %edx, (%ecx)    // *pstr = *str (str == edx)
null_pstr:
        movl    $1, %eax
        jmp     end
nfound: 
        xor     %eax, %eax
end:    mov     %ebp, %esp
        pop     %ebp
        ret

