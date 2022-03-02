        .text
        .global satsum
        .att_syntax noprefix

satsum:
        pushl   ebp
        movl    esp, ebp
        movl    8(ebp), eax
        movl    12(ebp), ecx
        addl    ecx, eax
        jnc     clear
        movl    $0, eax
        notl    eax

clear:
        popl    ebp
        ret
