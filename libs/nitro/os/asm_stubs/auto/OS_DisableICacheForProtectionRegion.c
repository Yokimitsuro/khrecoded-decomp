typedef unsigned int u32;

asm void OS_DisableICacheForProtectionRegion(register u32 flags)
{
    mrc p15, 0, r1, c2, c0, 1
    bic r1, r1, r0
    mcr p15, 0, r1, c2, c0, 1
    bx lr
}