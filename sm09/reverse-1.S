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

        subl    $4, %esp

get_num:
        lea     -16(%ebp), %eax

        push    %eax
        push    $Lscan
        call    scanf
        add     $8, %esp

        // %edi -- above top local variable
        // %esi -- iterator
        lea     -16(%ebp), %edi
        lea     -16(%ebp), %esi
        // Subtract 4 * num_items from %esp.
        mov     -16(%ebp), %eax
        cmpl    $0, %eax
        je      epilogue
        sub     %eax, %esp
        sub     %eax, %esp
        sub     %eax, %esp
        sub     %eax, %esp
        // %ebx -- iterator border
        movl    %esp, %ebx
        // Push num_items.
        push    %eax
        andl    $0xFFFFFFF0, %esp

scan_loop:
        lea     -4(%esi), %eax

        // scanf
        subl    $8, %esp
        push    %eax
        push    $Lscan
        call    scanf
        addl    $16, %esp
        // scanf

        subl    $4, %esi
        cmpl    %ebx, %esi
        jg      scan_loop
      
print_loop:

        // printf %d
        subl    $8, %esp
        push    (%esi)
        push    $Lprint
        call    printf
        addl    $16, %esp
        // printf %d

        addl    $4, %esi
        cmpl    %edi, %esi
        jne     print_loop

        // printf \n
        subl    $12, %esp
        push    $Lnl
        call    printf
        addl    $16, %esp
        // printf \n

        // Finish 16-align.
        movl    %ebx, %esp
        subl    $4, %esp
        // Pop num_items.
        pop     %eax
        // Multiply by 4.
        addl    %eax, %eax
        addl    %eax, %eax

        addl    %eax, %esp
        
epilogue:
        addl    $4, %esp

        pop     %ebx
        pop     %esi
        pop     %edi
        mov     %ebp, %esp
        pop     %ebp
        ret

