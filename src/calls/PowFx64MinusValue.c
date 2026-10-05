#include "nitro/types.h"

s64 PowFx64MinusValue(s64 base, s64 subtrahend, int exponent)
{
    int i;
    s64 result;

    i = 1;
    result = base;
    if (1 < exponent) {
        do {
            result = (result * base) >> 12;
            i = i + 1;
        } while (i < exponent);
    }
    return result - subtrahend;
}
