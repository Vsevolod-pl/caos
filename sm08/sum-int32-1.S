        .text
        .global main
main:
        xor     %ebx, %ebx
for_:   call    readi32
        jc      print_
        addl    %eax, %ebx
        jno     for_
overflow_:
        mov     %eax, %ebx
        sarl    $31, %ebx
        xorl    $0x7FFFFFFF, %ebx
        mov     %ebx, %eax
        call    writei32
        call    nl
        call    finish
print_:
        mov     %ebx, %eax
        call    writei32
        call    nl
        call    finish

