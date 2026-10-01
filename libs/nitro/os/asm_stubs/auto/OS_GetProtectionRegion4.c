typedef unsigned int u32;

asm u32 OS_GetProtectionRegion4(void)
{
    mrc p15, 0, r0, c6, c4, 0
    bx lr
}
