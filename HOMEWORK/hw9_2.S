        .att_syntax noprefix
        .global myhypot
        .text
myhypot:
        pushl   ebp
        movl    esp, ebp
        movsd   8(ebp), xmm1
        movsd   16(ebp), xmm2
        mulsd   xmm1, xmm1
        mulsd   xmm2, xmm2
        addsd   xmm2, xmm1
        sqrtsd  xmm1, xmm1
        movl    24(ebp), eax
        movsd   xmm1, (eax)
        popl     ebp
        ret
