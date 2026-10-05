#include "nitro/types.h"

extern s64 NewtonSolveFx64(s64 x, int param, s64 target, s64 (*valueFunc)(s64, s64, int), s64 (*slopeFunc)(s64, int), s32 tolerance);
extern s64 PowFx64MinusValue(s64 base, s64 subtrahend, int exponent);
extern s64 PowFx64DerivativeTimesN(s64 base, int n);

s64 NthRootFx64(s64 value, int n)
{
    s64 magnitude;
    s64 guess;

    if (value == 0) {
        return 0;
    }
    magnitude = value >= 0 ? value : -value;
    if (magnitude < 0x1000) {
        guess = value * 2;
    } else if (magnitude < 0xa000) {
        guess = value / 4;
    } else if (magnitude < 0x64000) {
        guess = value / 16;
    } else if (magnitude < 0x3e8000) {
        guess = value / 64;
    } else if (magnitude < 0x2710000) {
        guess = value / 256;
    } else if (magnitude < (s32)0xf4240000) {
        guess = value / 0x1000;
    } else if (magnitude < 0x174876e800000LL) {
        guess = value / 0x10000;
    } else {
        guess = value / 0x200000000LL;
    }
    return NewtonSolveFx64(guess, n, value, PowFx64MinusValue, PowFx64DerivativeTimesN, 16);
}
