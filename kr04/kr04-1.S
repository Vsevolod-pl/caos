        .text
        .global forward.args
forward.args:
        // 8: v1, 4: v2, 4: v3
        push    %ebp
        mov     %esp, %ebp
        // 8(%ebp) == v1
        // 16(%ebp) == v2
        // 20(%ebp) == v3
        subl    $12, %esp
        andl    $0xFFFFFFF0, %esp
        
        movl    8(%ebp), %eax
        push    %eax
        
        movl    16(%ebp), %eax
        cdq
        push    %edx
        push    %eax
        movl    20(%ebp), %eax
        push    %eax
        call    process

        negl    %eax

        mov     %ebp, %esp
        pop     %ebp
        ret
