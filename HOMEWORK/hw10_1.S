#include <asm/unistd_32.h>
        .data
c:      .byte   0
        .text
        .global _start
        .att_syntax noprefix
_start:
        movl $__NR_read, eax
        movl $0, ebx
        movl $c, ecx
        movl $1, edx
        int $0x80
        cmpl $0, eax
        je end
        cmpl $'1', c
        jl write_char
        cmpl $'9', c
        jg write_char
        movl $'0', c
        jmp write_char
write_char:
        movl    $__NR_write, eax
        movl    $1, ebx
        movl    $c, ecx
        movl    $1, edx
        int     $0x80
        jmp     _start
end:
        movl $__NR_exit, eax
        xorl ebx, ebx
        int $0x80
