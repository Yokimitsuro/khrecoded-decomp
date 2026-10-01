typedef unsigned int u32;

asm u32 OS_GetProtectionRegion7(void)
{
    mrc p15, 0, r0, c6, c7, 0
    bx lr
}
