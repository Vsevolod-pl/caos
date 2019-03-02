        .text
        .global process
process:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi
        push    %ebx

        movl    8(%ebp), %edi
        // %edi = *p
        movl    0(%edi), %esi
        // %esi = *v1
        movl    12(%ebp), %eax
        movl    $8, %ebx
        imull   %ebx
        addl    %eax, %esi

v1:
        subl    $8, %esp
        movl    0(%esi), %eax
        movl    %eax, 0(%esp)
        movl    4(%esi), %eax
        movl    %eax, 4(%esp)
        movsd   (%esp), %xmm0
        addl    $8, %esp

v2:     
        mov     %edi, %esi
        // %esi = *p
        addl    $28, %esi
        movl    12(%ebp), %eax
        movl    $8, %ebx
        imull   %ebx
        subl    %eax, %esi
        

        subl    $8, %esp
        movl    0(%esi), %eax
        movl    %eax, 0(%esp)
        movl    4(%esi), %eax
        movl    %eax, 4(%esp)
        movsd   (%esp), %xmm1
        addl    $8, %esp


        subsd   %xmm1, %xmm0
        mulsd   %xmm0, %xmm0

return: subl    $8, %esp
        movsd   %xmm0, (%esp)
        movl    0(%esp), %eax
        movl    %eax, 36(%edi)
        movl    4(%esp), %eax
        movl    %eax, 40(%edi)
        addl    $8, %esp

        pop     %ebx
        pop     %edi
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret
