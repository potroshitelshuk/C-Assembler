        .text
        .global satsum
satsum:   	
	push	{ fp, lr }
	ldr 	r0, =A
	ldr     r0, [r0]
	ldr		r3, =B
	ldr     r3, [r3]
	add		r1, r0, r3
	add		r2, r3, r1
	add		r3, r2, r1
	adr     r0, sfmt
	bl		printf
	mov 	r0, #0
	pop		{ fp, pc }
sfmt:	.asciz  "%d %d %d\n"



