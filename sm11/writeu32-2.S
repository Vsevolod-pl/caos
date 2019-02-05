writeu32:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi
        push    %ebx

        

        pop     %ebx
        pop     %edi
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret
