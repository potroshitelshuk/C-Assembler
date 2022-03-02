spec:   .asciz "%d %d %d\n"
        .text
	.global print_fib
        .att_syntax noprefix

print_fib:
	pushl   ebp
        movl    esp, ebp
        movl    A, edx
        addl    B, edx
        movl    edx, ecx
        addl    B, ecx
        movl    ecx, eax
        addl    edx, eax
        pushl   eax
        pushl   ecx
        pushl   edx
        pushl   $spec
        call    printf
        addl    $16, esp
        popl    ebp
        movl    $0, eax
        ret
