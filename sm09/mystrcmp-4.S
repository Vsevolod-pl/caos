        .text
        .global mystrcmp
mystrcmp:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi

        mov     8(%ebp), %esi
        mov     12(%ebp), %edi

L2:     movzb   (%esi), %eax
        movzb   (%edi), %edx
        inc     %esi
        inc     %edi
        sub     %edx, %eax
        jnz     L1
        test    %edx, %edx
        jnz     L2
 
L1:     pop     %edi
        pop     %esi
        pop     %ebp
        ret
