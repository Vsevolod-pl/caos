        .text
        .global main
main:                           /* %esi is even sum, %edi is odd sum */
        xor     %esi, %esi
        xor     %edi, %edi
for_:   call    readi32
        jc      print_
        mov     %eax, %ebx
        andl    $0x00000001, %eax
        test    %eax, %eax
        jz      even_
        jnz     odd_

print_: mov     %esi, %eax
        call    writei32
        call    nl
        mov     %edi, %eax
        call    writei32
        call    nl
        call    finish

even_:  add     %ebx, %esi
        jmp     for_

odd_:   add     %ebx, %edi
        jmp     for_

