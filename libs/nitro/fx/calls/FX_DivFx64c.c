extern void FX_DivAsync(int numerator, int denominator);

long long FX_DivFx64c(int numerator, int denominator)
{
    volatile unsigned short *divisionControl =
        (volatile unsigned short *)0x04000280;

    FX_DivAsync(numerator, denominator);
    while (*divisionControl & 0x8000) {
    }
    return *(long long *)0x040002a0;
}
