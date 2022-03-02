        .text
        .global mystrcmp
mystrcmp:
        push %ebp
        mov %esp, %ebp
        push %esi
        push %edi
        mov 8(%ebp), %esi
        mov 12(%ebp), %edi
for:
        movb (%esi), %al
        movb (%edi), %cl
        cmpb %al, %cl
        ja less
        jb more
        testb %al, %al
        jz equal
        inc %esi
        inc %edi
        jmp for
more:
        mov $1, %eax
        jmp clear
less:
        mov $-1, %eax
        jmp clear
equal:
        mov $0, %eax
clear:
        pop %edi
        pop %esi
        pop %ebp
        ret
