// instruction arguments must start at column 16 or 24 (but starts at 17)
// GREAT! EXCELLENT CODE STYLE!
	.text
	.global satsum
satsum:
	push	{ fp, lr }
	adds	r0, r0, r1
	movcs	r0, #0xffffffff // mx_num
	pop		{ fp, pc }