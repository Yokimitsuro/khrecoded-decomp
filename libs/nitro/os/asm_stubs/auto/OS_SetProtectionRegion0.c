typedef unsigned int u32;

asm void OS_SetProtectionRegion0(u32 parameter)
{
    mcr p15, 0, r0, c6, c0, 0
    bx lr
}
