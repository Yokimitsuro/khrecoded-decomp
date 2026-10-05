#include "nitro/types.h"

s32 SignNonNegativeOne(s32 value)
{
    s32 sign;
    if (value >= 0) {
        sign = 1;
    } else {
        sign = -1;
    }
    return sign;
}
