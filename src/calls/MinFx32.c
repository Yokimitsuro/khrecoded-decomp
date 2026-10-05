#include "nitro/types.h"

s32 MinFx32(s32 a, s32 b)
{
    if (a > b) {
        a = b;
    }
    return a;
}
