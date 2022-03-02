        .att_syntax noprefix
        .section .text
        .global process
process:
        push    ebp
        movl    esp, ebp
        pushl   edx // counter
        subl    $8, esp
        leal    -4(ebp), eax
        movl    $0, -8(ebp)
        push    eax
        push    $format1
        // read n
        call    scanf
        addl    $8, esp
        cmpl    $0, -4(ebp)
        jne     cin
        je      clear
cin:
        subl    $4, esp
        leal    (esp), eax
        push    eax
        push    $format1
        // read x
        call    scanf
        addl    $8, esp
        incl    -8(ebp)
        movl    -8(ebp), eax
        cmpl    eax, -4(ebp)
        jne     cin
        movl    $0, -8(ebp)
cout:
        push    $format2
        // write x
        call    printf
        addl    $8, esp
        incl    -8(ebp)
        movl    -8(ebp), eax
        cmpl    eax, -4(ebp)
        jne     cout
        je      clear
clear:
        // write \n
        push    $format_nl
        call    printf
        leave
        ret
// frmts
        .section .rodata
format1:        .string "%d"
format2:        .string "%d "
format_nl:      .string "\n"
x:              .int 0