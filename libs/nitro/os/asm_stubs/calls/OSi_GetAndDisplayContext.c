extern void OSi_SetExContext(void);
extern void func_02003e3c(void);

asm void OSi_GetAndDisplayContext(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_SetExContext
    bl func_02003e3c
    ldmia sp!, {r0, lr}
    bx lr
}
