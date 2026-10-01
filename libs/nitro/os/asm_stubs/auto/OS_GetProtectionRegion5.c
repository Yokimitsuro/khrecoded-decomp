typedef unsigned int u32;

asm u32 OS_GetProtectionRegion5(void)
{
    mrc p15, 0, r0, c6, c5, 0
    bx lr
}
