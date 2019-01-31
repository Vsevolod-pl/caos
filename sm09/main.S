        .text
        .global main
main:
        movl    $0x42, %ebx
        movl    $0x43, %esi
        movl    $0x44, %edi
        movl    $0x45, %ebp

        movl    %esp, %eax
        call    writei32
        call    nl
        subl    $12, %esp
        call    process
        addl    $12, %esp
        movl    %esp, %eax
        call    writei32
        call    nl

        movl    %ebx, %eax
        call    writei32
        call    nl
        movl    %esi, %eax
        call    writei32
        call    nl
        movl    %edi, %eax
        call    writei32
        call    nl
        movl    %ebp, %eax
        call    writei32
        call    nl

        call    finish
