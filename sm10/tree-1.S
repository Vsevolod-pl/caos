        .text
        .align  16
eps:    .double 1e-8

        .align  16
        .global tree_find
tree_find:
        push    %ebp
        mov     %esp, %ebp

        // 8(%ebp) == *root == %eax -> %xmm1
        // 12(%ebp) == key == %xmm0
        // 20(%ebp) == **pstr

        // Check for null root.
        movl    8(%ebp), %eax
        test    %eax, %eax
        je      nfound

        movsd   12(%ebp), %xmm0
        // key;     0(%eax)
        // *left;   8(%eax)
        // *right;  12(%eax)
        // *str;    16(%eax)
compare:
        // key -> %xmm0
        // item -> %xmm1, %xmm2
        movsd   0(%eax), %xmm1
        movsd   0(%eax), %xmm2
        subsd   %xmm0, %xmm1
        comisd  eps, %xmm1
        jbe     found
        // %xmm0 == 4.9 %xmm2 == 4.6667
ne:     comisd  %xmm0, %xmm2
        jb      to_right
        ja      to_left
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


found:  mov     20(%ebp), %edx // **pstr -> %edx
        // Check for null pstr.
        test    %edx, %edx  // **pstr == 0?
        jz      null_pstr
        // *pstr -> %edx
        mov     (%edx), %ecx // **pstr ->
        mov     (%edx), %edx
        mov     (%ecx), %ecx
        mov     16(%eax), %
null_pstr:
        movl    $1, %eax
        jmp     end
nfound: 
        xor     %eax, %eax
end:    mov     %ebp, %esp
        pop     %ebp
        ret

