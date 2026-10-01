typedef unsigned int u32;

asm void MIi_CpuClear32(register u32 value,
                                    register void *destination,
                                    register u32 size)
{
    add     ip, r1, r2
clearNextWord:
    cmp     r1, ip
    stmltia r1!, {r0}
    blt     clearNextWord
    bx      lr
}
