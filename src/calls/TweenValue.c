#include "nitro/types.h"

#define REG_DIVCNT (*(vu16 *)0x04000280)
#define REG_DIV_NUMER (*(s64 *)0x04000290)
#define REG_DIV_DENOM (*(u64 *)0x04000298)
#define REG_DIV_RESULT32 (*(vs32 *)0x040002a0)

extern int FX_Div(int numer, int denom);
extern int LerpBySquaredRatio(int from, int to, u32 step, u32 total);
extern int LerpBySquaredRemaining(int from, int to, u32 step, u32 total);

static inline s32 MulFx32(s32 a, s32 b)
{
    return (s32)(((s64)a * b + 0x800) >> 12);
}

s32 TweenValue(s32 start, s32 end, u32 elapsed, u32 duration, u32 curve)
{
    s32 diff;
    s32 offsetFromMid;
    s32 halfDiff;
    s32 offsetSq;
    u32 half;
    s32 eased;

    if (start == end) {
        return end;
    }
    if (elapsed >= duration) {
        return end;
    }

    diff = end - start;

    switch (curve) {
    case 0:
        REG_DIVCNT = 1;
        REG_DIV_NUMER = (s64)diff * elapsed;
        REG_DIV_DENOM = (u64)duration;
        while (REG_DIVCNT & 0x8000) {
        }
        return start + REG_DIV_RESULT32;
    case 1:
        return LerpBySquaredRatio(start, end, elapsed, duration);
    case 2:
        return LerpBySquaredRemaining(start, end, elapsed, duration);
    case 3:
        offsetFromMid = 0x1000 - (FX_Div(elapsed, duration) << 1);
        if (elapsed < (duration >> 1)) {
            offsetSq = MulFx32(offsetFromMid, offsetFromMid);
            halfDiff = diff / 2;
            eased = MulFx32(halfDiff, 0x1000 - offsetSq);
            return eased + start;
        } else {
            offsetSq = MulFx32(offsetFromMid, offsetFromMid);
            halfDiff = diff / 2;
            eased = MulFx32(halfDiff, offsetSq);
            return start + halfDiff + eased;
        }
    case 4:
        halfDiff = diff / 2;
        half = duration >> 1;
        if (elapsed < half) {
            return LerpBySquaredRatio(start, end - halfDiff, elapsed, half);
        }
        return LerpBySquaredRemaining(start + halfDiff, end, elapsed - half, half);
    }
}
