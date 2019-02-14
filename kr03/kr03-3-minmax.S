        .text
        .global minmax
minmax:
        push    %ebp
        mov     %esp, %ebp
        push    %edi
        push    %esi
        push    %ebx


        mov     %edx, %ebx
        //      esi == min, edi == max
        mov     (%eax), %esi
        mov     (%eax), %edi
loop:
        cmpl    (%eax), %esi
        cmovg   (%eax), %esi
        cmpl    (%eax), %edi
        cmovl   (%eax), %edi

        addl    $4, %eax
        decl    %ebx
        cmpl    $0, %ebx

        jne     loop


end:
        mov     %esi, %eax
        mov     %edi, %edx
        pop     %ebx
        pop     %esi
        pop     %edi
        mov     %ebp, %esp
        pop     %ebp
        ret
