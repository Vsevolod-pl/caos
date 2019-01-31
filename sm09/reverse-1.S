        .text
        .align  16
Lprint: .asciz  "%d "
        .align  16
Lscan:  .asciz  "%d"
        .align  16
Lnl:    .asciz  "\n"

        .global process
process:
        push    %ebp
        mov     %esp, %ebp
        push    %edi
        push    %esi
        push    %ebx
 
get_num:
        sub     $4, %esp
        lea     0(%esp), %eax
        push    %eax
        push    $Lscan
        call    scanf
        add     $8, %esp
        // %edi -- above top local variable
        // %esi -- iterator
        mov     %esp, %edi
        mov     %esp, %esi
        // Subtract 4 * num_items from %esp.
        mov     0(%esp), %eax
        cmpl    $0, %eax
        je      epilogue
        sub     %eax, %esp
        sub     %eax, %esp
        sub     %eax, %esp
        sub     %eax, %esp
        // %ebx -- iterator border
        movl    %esp, %ebx
        andl    $0xFFFFFFF0, %esp

scan_loop:
        lea     -4(%esi), %eax
        subl    $8, %esp
        push    %eax
        push    $Lscan
        call    scanf
        addl    $16, %esp
        subl    $4, %esi
        cmpl    %ebx, %esi
        jg      scan_loop
      
print_loop:
        subl    $8, %esp
        push    (%esi)
        push    $Lprint
        call    printf
        addl    $16, %esp
        addl    $4, %esi
        cmpl    %edi, %esi
        jne     print_loop

        subl    $12, %esp
        push    $Lnl
        call    printf
        addl    $16, %esp
epilogue:
        mov     %ebp, %esp
        subl    $8, %esp
        pop     %ebx
        pop     %esi
        pop     %edi
        mov     %ebp, %esp
        pop     %ebp
        ret

