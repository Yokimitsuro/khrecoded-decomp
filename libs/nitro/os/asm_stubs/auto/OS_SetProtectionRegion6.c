typedef unsigned int u32;

asm void OS_SetProtectionRegion6(u32 parameter)
{
    mcr p15, 0, r0, c6, c6, 0
    bx lr
}
