int FX_GetDivResult(void)
{
    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }
    return (int)((*(long long *)0x040002a0 + 0x80000) >> 20);
}