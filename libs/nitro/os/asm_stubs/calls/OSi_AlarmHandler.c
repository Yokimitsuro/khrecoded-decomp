extern void OSi_ArrangeTimer(void);

asm void OSi_AlarmHandler(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_ArrangeTimer
    ldmia sp!, {r0, lr}
    bx lr
}
