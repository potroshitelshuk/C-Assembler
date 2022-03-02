// compare two strings        
        .text
        .global mystrcmp
mystrcmp:
        push    { fp, lr }              @standart
        mov     r12, #0                 @standart
cycle:
        ldrb    r2, [r0, r12]
        ldrb    r3, [r1, r12]
        tst     r2, r3          @ r2 < r3 || r2 == r3 || r2 > r3
        beq     finish             @ jmp --> finish
        add     r12, r12, #1
        cmp     r2, r3
        beq     cycle                   @jmp --> cycle
finish:
        sub     r0, r2, r3
        pop     { fp, pc }                      @standart