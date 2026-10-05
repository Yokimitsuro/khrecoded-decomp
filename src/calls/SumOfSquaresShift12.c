#include "nitro/types.h"

extern s64 Square64(s32 value);

u32 SumOfSquaresShift12(s32 a, s32 b)
{
    s64 sum = Square64(a) + Square64(b);
    return (u32)(sum >> 0xc);
}
