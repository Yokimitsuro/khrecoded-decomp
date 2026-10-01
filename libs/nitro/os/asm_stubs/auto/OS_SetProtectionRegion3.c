typedef unsigned int u32;

asm void OS_SetProtectionRegion3(u32 parameter)
{
    mcr p15, 0, r0, c6, c3, 0
    bx lr
}
