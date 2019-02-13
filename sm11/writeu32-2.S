        .global writeu32
writeu32:
        push    %ebp
        mov     %esp, %ebp
        push    %esi
        push    %edi
        push    %ebx
        // -12(%ebp)
        subl    $84, %esp
        // e.g. 4294967295:
        // -52(%ebp)..-16(%ebp) == 10^9, 10^8, 10^7, ..., 10^1, 10^0
        // -92(%ebp)..-56(%ebp) == '4', '2', '9', ..., '9', '5'
        // -96(%ebp) == dumb space

        leal    -92(%ebp), %esi  // up-iterator
        leal    -52(%ebp), %edi  // stopper
        // Put '0' to digits
zeroize:
        movl    $'0', (%esi)
        addl    $4, %esi
        cmpl    %esi, %edi
        jne     zeroize

        movl    $1, -16(%ebp)  // 10^0
        leal    -20(%ebp), %esi  // down-iterator
        leal    -56(%ebp), %edi  // stopper
        // Get 10^0, 10^1, .., 10^9
mul10:
        movl    4(%esi), %eax
        mull    $10
        movl    %eax, (%esi)  // 10 * 10^{i - 1}
        subl    $4, %esi
        cmpl    %esi, %edi
        jne     mul10

        leal    -92(%ebp), %esi  // up-iterator
        leal    -52(%ebp), %edi  // stopper
        // Factorize by 10 powers while getting all digits.
        // %ecx <- n
factorize:
        // 10^i -> %eax
        // n -> %ecx
        movl    40(%esi), %eax
one_digit:
        incl    (%esi)
        subl    %eax, %ecx
        jnc     one_digit
        // If carry shit happened, the last subtraction wasn't needed, add 10^i back.
        addl    %eax, %ecx
        decl    (%esi)
        addl    $4, %esi
        cmpl    %esi, %edi
        jne     factorize
        
        leal    -96(%ebp), %esi  // up-iterator
        leal    -52(%ebp), %edi  // stopper
// skip all leading zeros
skip_zero_loop:
        addl    $4, %esi
        cmpl    %esi, %edi
        je      write_zero
        movl    (%esi), %eax
        cmpl    $'0', %eax
        je      skip_zero_loop

// write all digits
write_digit:
        movl    (%esi), %ecx
        // !!! HOW TO PUT SMTH ON %EDX? WHAT DO WE NEED TO PUT ON THIS???
        ...
        call    writechar
        addl    $4, %esi
        cmpl    %esi, %edi
        jne     write_digit

end:
        add     $84, %esp
        pop     %ebx
        pop     %edi
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret

// Number is 0. Print it especially like nothing before!
write_zero:
        movl    $'0', %ecx
        ...
        call    writechar
        ret
