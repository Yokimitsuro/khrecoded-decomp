#include "nitro/types.h"

s32 IntPow(s32 base, s32 exponent)
{
    s32 count;
    s32 result;

    result = 1;
    count = 0;
    if (0 < exponent) {
        do {
            result = base * result;
            count = count + 1;
        } while (count < exponent);
    }
    return result;
}
