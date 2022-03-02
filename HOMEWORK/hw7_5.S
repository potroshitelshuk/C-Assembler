
    .text
	.att_syntax noprefix
    .global main

main:
     	mov     $0, edi
        mov     $0, esi
        call    read
read:
     	call    readi32
        jc		print
        mov     eax, ebx
        test    $1, eax
        jnz     add_odd
        addl    ebx, esi
        jmp     read
print:
      	movl    esi, eax
        call    writei32
        call    nl
        movl    edi, eax
        call    writei32
        call    nl
        call    finish

add_odd:
        addl    ebx, edi
        jmp     read



