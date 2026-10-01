typedef unsigned int u32;
typedef unsigned long long u64;

extern int FX_GetSqrtResult(void);

int FX_Sqrt(int x)
{
    if (x > 0) {
        *(volatile unsigned short *)0x040002b0 = 1;
        *(volatile u64 *)0x040002b8 = (u64)(u32)x << 32;
        return FX_GetSqrtResult();
    }
    return 0;
}
