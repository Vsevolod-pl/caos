        .text
        .global main
main:
        call    readi32
        movl    %eax, %ebx
for_:   
        cmpl    $0, %ebx
        jl      final_
        movl    %ebx, %eax
        call    writei32
        call    nl
        subl    $1, %ebx
        jmp     for_

final_: 
        call    finish
