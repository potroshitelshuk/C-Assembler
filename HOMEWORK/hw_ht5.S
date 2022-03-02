// instruction arguments must start at column 16 or 24 (but starts at 17)
// GREAT! EXCELLENT CODE STYLE!
	.text
	.global process
// i hate assembler
process:
	push	{ fp, lr }
	ldr		r1, [r0, r1, lsl #2] // m[i] --> r1
	add  	r0, r0, r2, lsl #2 // r0 += 4 * r2
	ldr  	r0, [r0, #64] // m[j] --> r2
	add  	r0, r0, r1
	add  	r0, r0, r0, lsr #31
	asr  	r0, r0, #1 // r0 /= 2
	pop  	{ fp, pc }