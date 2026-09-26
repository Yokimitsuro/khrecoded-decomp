extern void func_02004450(void);

asm void OSi_AlarmHandler(void)
{
    stmdb sp!, {r0, lr}
    bl func_02004450
    ldmia sp!, {r0, lr}
    bx lr
}
