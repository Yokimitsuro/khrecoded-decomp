typedef unsigned int u32;

asm u32 OS_GetProtectionRegion0(void)
{
    mrc p15, 0, r0, c6, c0, 0
    bx lr
}
