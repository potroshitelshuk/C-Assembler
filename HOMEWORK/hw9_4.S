    .text
	.global dot_product
    .att_syntax noprefix

dot_product:
	push    ebp
    movl    esp, ebp
    movl    8(ebp), eax
    movl    12(ebp), ecx
    movl    16(ebp), edx
    pxor    xmm0, xmm0

while:   
    cmpl    $0, eax
    je	    end
    movss   (ecx), xmm1
    movss   (edx), xmm2
    mulss   xmm2, xmm1
    addss   xmm1, xmm0
    add     $4, ecx
    add     $4, edx
    dec     eax
    jmp     while
end:
    sub     $16, esp
    movss   xmm0, (esp)
    flds    (esp)
    add     $16, esp
    pop     ebp
    ret
