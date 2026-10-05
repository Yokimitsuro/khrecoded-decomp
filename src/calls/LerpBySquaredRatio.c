#include "nitro/types.h"

#define REG_DIVCNT (*(vu16 *)0x04000280)

static inline void SetDiv64_64(u64 numer, u64 denom)
{
    REG_DIVCNT = 2;
    *(u64 *)0x04000290 = numer;
    *(u64 *)0x04000298 = denom;
}

static inline u64 GetDivResult64(void)
{
    while (REG_DIVCNT & 0x8000) {
    }
    return *(u64 *)0x040002a0;
}

int LerpBySquaredRatio(int from, int to, u32 step, u32 total)
{
    u64 stepSquared;

    SetDiv64_64((u64)(u32)(to - from) << 32, (u64)total * total);
    stepSquared = step * step;
    return from + (int)((stepSquared * GetDivResult64()) >> 32);
}
