#include "nitro/types.h"

s32 IntMax(s32 a, s32 b)
{
    if (a < b) {
        a = b;
    }
    return a;
}
