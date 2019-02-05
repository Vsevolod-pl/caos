        .text

        .global process
process:
        push    %ebp
        mov     %esp, %ebp
        push    %ebx

        //      8ebp == res 16ebp == a 17ebp == b 20???        




        xorl    %eax, %eax

        movl    $5, %ecx
        movl    16(%ebp), %eax
        imull   %ecx


        jo      overflow
        movl    %eax, %ebx

        xorl    %eax, %eax
        movl    12(%ebp), %eax
        // andl    $0x0000FFFF, %eax


        movl    $4, %ecx
        imull   %ecx

        jo      overflow
        subl    %eax, %ebx



        jo      overflow


        mov     8(%ebp), %eax 
        mov     %ebx, (%eax)     
        mov     $0, %eax


end:
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret


overflow:
        movl    $1, %eax
        jmp     end
