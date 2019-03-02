        .text
        .global forward.args
forward.args:
        push    %ebp
        mov     %esp, %ebp
        subl    $12, %esp
        push    8(%ebp)
        push    $0
        push    16(%ebp)
        movl    20(%ebp), %ecx
        call    process

        addl    $12, %esp
        addl    $12, %esp
        mov     %ebp, %esp
        pop     %ebp
        xorl    %edx, %edx
        ret
