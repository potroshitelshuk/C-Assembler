		.text
	.att_syntax noprefix
	.global process

process:
	movl A, ecx
	movl B, eax
	imull  ecx
	movl eax, ecx
	movl C, edx
	movl D, eax
	imull edx
	subl eax, ecx
	movl ecx, R
	ret

	.data
A:	.int 1
B:	.int 2
C:	.int 3
D:	.int 4
R:	.int 0
	.global A, B, C, D, R
