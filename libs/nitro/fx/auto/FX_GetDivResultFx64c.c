long long FX_GetDivResultFx64c(void)
{
    volatile unsigned short *divisionControl =
        (volatile unsigned short *)0x04000280;

    while (*divisionControl & 0x8000) {
    }
    return *(long long *)0x040002a0;
}
