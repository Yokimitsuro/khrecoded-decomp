extern void OS_UnlockCartridge_0x020022c8(int processor);

asm void OS_UnLockCartridge(int processor)
{
    ldr r1, =OS_UnlockCartridge_0x020022c8
    bx  r1
}
