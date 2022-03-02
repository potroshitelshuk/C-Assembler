    .section .text
    .att_syntax noprefix
    .global process

process:
    pushl   ebp
    movl    esp, ebp
    pushl   esi
    movl    8(ebp), esi
    movl    12(ebp), ecx
    movl    16(ebp), edx
    movl    (esi, ecx, 4), eax
    addl    64(esi, edx, 4), eax
    sarl    $1, eax
    jnc     end
    cmpl    $0, eax
    jge      end
    addl    $1, eax

end:
	popl     esi
    popl     ebp
    ret