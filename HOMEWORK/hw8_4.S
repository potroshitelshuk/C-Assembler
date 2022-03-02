        .att_syntax noprefix
        .text
        .global process
process:
        pushl   ebp
        movl    esp, ebp
        subl    $20, esp
        movl    $0, -4(ebp)

        jmp     read
r:
        movl    -12(ebp), eax
        cmpl    eax, -20(ebp)
        jle     l
        movl    -12(ebp), eax
        movl    eax, -20(ebp)
l:
        movl    -8(ebp), eax
        cmpl    eax, -16(ebp)
        jge     sum
        movl    -8(ebp), eax
        movl    eax, -16(ebp)
sum:
        movl    -20(ebp), eax
        subl    -16(ebp), eax
        cltd
        notl    edx
        andl    edx, eax
        addl    eax, -4(ebp)

read:
        leal    -20(ebp), eax
        pushl   eax
        leal    -16(ebp), eax 
        pushl   eax
        leal    -12(ebp), eax 
        pushl   eax
        leal    -8(ebp), eax 
        pushl   eax
        pushl   $frmt1
        call    scanf
        cmpl    $4, eax
        je      r
        pushl   -4(ebp)
        pushl   $frmt2
        call    printf
        movl    ebp, esp
        movl    $0, eax
        popl    ebp
        ret

        .data
frmt1:  .string "%d %d %d %d"
frmt2:  .string "%d\n"
a1:     .int 0
b1:     .int 0
a2:     .int 0
b2:     .int 0
res:    .int 0
