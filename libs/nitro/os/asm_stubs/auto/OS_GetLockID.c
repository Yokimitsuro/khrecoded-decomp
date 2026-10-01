asm int OS_GetLockID(void)
{
    ldr     r3, =0x02ffffb0
    ldr     r1, [r3]
    clz     r2, r1
    cmp     r2, #0x20
    movne   r0, #0x40
    bne     found
    add     r3, r3, #4
    ldr     r1, [r3]
    clz     r2, r1
    cmp     r2, #0x20
    ldr     r0, =0xfffffffd
    bxeq    lr
    mov     r0, #0x60
found:
    add     r0, r0, r2
    mov     r1, #0x80000000
    mov     r1, r1, lsr r2
    ldr     r2, [r3]
    bic     r2, r2, r1
    str     r2, [r3]
    bx      lr
}