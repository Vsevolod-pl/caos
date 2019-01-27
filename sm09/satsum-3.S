        .global satsum
        .text
satsum:
        push    %ebp
        mov     %esp, %ebp

        mov     8(%ebp), %eax
        add     12(%ebp), %eax
        jnc     L1
        mov     $0xFFFFFFFF, %eax
        
L1:     popl    %ebp
        ret
