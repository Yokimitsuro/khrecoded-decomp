#include "nitro/types.h"

extern int _s32_div_f(int numerator, int denominator);

BOOL CheckedMultiply(int *value, int factor)
{
    int multiplicand = *value;
    int multiplier = factor;
    int sign = ((multiplicand < 0) ^ (multiplier < 0)) ? -1 : 1;

    if (multiplicand < 0) {
        multiplicand = -multiplicand;
    }
    if (multiplier < 0) {
        multiplier = -multiplier;
    }
    if (multiplicand > _s32_div_f(0x7fffffff, multiplier)) {
        return FALSE;
    }

    *value = multiplicand * multiplier * sign;
    return TRUE;
}
