#include "nitro/types.h"

extern s32 _s32_div_f(s32 dividend, s32 divisor);

s32 DigitCount(s32 value)
{
    s32 count;

    count = 0;
    do {
        count = count + 1;
        value = _s32_div_f(value, 10);
    } while (0 < value);
    return count;
}
