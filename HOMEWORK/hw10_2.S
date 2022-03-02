#include <asm/unistd_32.h>
        .att_syntax noprefix
        .text
        .global _start
_start:
        movl    $__NR_read, eax
        movl    $0, ebx
        leal    (esp), ecx
        movl    $1, edx
        int     $0x80
        cmpl    $0, eax
        je      end
	cmpl   $'a', (esp)
	jl     write_char
	cmpl   $'z', (esp)
	jg     write_char
	subl   $32, (esp)
write_char:
        movl    $__NR_write, eax
        movl    $1, ebx
        leal    (esp), ecx
        movl    $1, edx
        int     $0x80
        jmp     _start
end:
        movl    $__NR_exit, eax
        xorl    ebx, ebx
        int     $0x80
