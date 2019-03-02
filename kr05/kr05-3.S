        .text
        .global countrec
countrec:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi
        push    %ebx

        movl    8(%ebp), %esi
        // %esi == *cntx
        movl    8(%esi), %edi
        // %edi == *out

        call    0(%esi)

        // Write to *out
        movl    %ebx, (%edi)

        pop     %ebx
        pop     %edi
        pop     %esi
        mov     %ebp, %esp
        ret
