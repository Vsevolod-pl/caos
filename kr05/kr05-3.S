        .text
        .global countrec
countrec:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %ebx

        // %esi == *cntx
        movl    8(%ebp), %esi
        // eax = addr
        movl    0(%esi), %eax
        // ecx = size
        movl    4(%esi), %ecx
        // ecx = addr + size
        addl    %eax, %ecx
        // %esi == *out
        movl    8(%esi), %esi

        // counter -- ebx
        xorl    %ebx, %ebx
loop:
        cmpl    4(%ebp), %eax
        jg      dont
        cmpl    4(%ebp), %ecx
        jle     dont
        addl    $1, %ebx
dont:   movl    (%ebp), %ebp
        test    %ebp, %ebp
        jne     loop

end:
        // Write result to *out
        movl    %ebx, (%esi)

        pop     %ebx
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret

