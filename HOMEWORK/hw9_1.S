        .att_syntax noprefix
        .text
        .global process
process:
        push    ebp
        movl    esp, ebp
        subl    $8, esp
        movq    B, mm1
        movq    A, mm2
        psllq   $1, mm2
        psrlq   $1, mm1
        psubq   mm1, mm2
        movq    mm2, (esp)
        push    $frmt
        call    printf
        movl    ebp, esp
        popl    ebp
        ret


frmt:   .asciz  "%llu\n"
