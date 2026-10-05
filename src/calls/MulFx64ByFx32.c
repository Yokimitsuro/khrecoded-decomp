#include "nitro/types.h"

s64 MulFx64ByFx32(s64 a, s32 b)
{
    return (a * b) >> 12;
}
