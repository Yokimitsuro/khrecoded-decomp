typedef unsigned int u32;

asm void OS_SetProtectionRegion4(u32 parameter)
{
    mcr p15, 0, r0, c6, c4, 0
    bx lr
}
