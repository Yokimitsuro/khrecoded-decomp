extern void FX_InvAsync(int denominator);

long long FX_InvFx64c(int denominator)
{
    volatile unsigned short *divisionControl =
        (volatile unsigned short *)0x04000280;

    FX_InvAsync(denominator);
    while (*divisionControl & 0x8000) {
    }
    return *(long long *)0x040002a0;
}
