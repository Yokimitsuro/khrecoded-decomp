#include "nitro/types.h"

u32 MultiplyShiftRight27(s32 a, s32 b)
{
    return (u32)(((s64)a * b) >> 0x1b);
}
