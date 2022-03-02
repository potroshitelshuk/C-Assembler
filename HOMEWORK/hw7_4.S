	.text
	.att_syntax noprefix
	.global main

main:
	mov	$0, ebx
	call	read

read:
	call	readi32
	jc 		print
	addl	eax, ebx
	jno		read
	jo		fix

print:
	mov		ebx, eax
	call	writei32
	call	nl
	call	finish

fix:
	adcl    $0, ecx
    movl    $2147483646, ebx
    addl    ecx, ebx
	call	print

