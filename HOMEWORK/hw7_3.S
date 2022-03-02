    .text
	.att_syntax noprefix
    .global main

main:
     	call readi32
        mov eax, ebx
        test ebx, ebx
        jge loop
        call finish
loop:
     	mov ebx, eax
        call writei32
        call nl
        dec ebx
        test ebx, ebx
        jge loop
        call finish