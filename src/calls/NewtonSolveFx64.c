#include "nitro/types.h"

extern s64 _ll_sdiv(s64 numerator, s64 denominator);

s64 NewtonSolveFx64(s64 x, int param, s64 target, s64 (*valueFunc)(s64, s64, int), s64 (*slopeFunc)(s64, int), s32 tolerance)
{
    u16 i;
    s64 next;
    s64 diff;
    s64 slope;

    for (i = 0; i < 1000; i++) {
        slope = slopeFunc(x, param);
        next = x - _ll_sdiv(valueFunc(x, target, param) << 12, slope);
        diff = next - x;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < tolerance) {
            return next;
        }
        x = next;
    }
    return x;
}
