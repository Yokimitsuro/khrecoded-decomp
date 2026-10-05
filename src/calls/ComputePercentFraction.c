#include "nitro/types.h"

extern s32 _s32_div_f(s32 numerator, s32 denominator);

void ComputePercentFraction(u8 *obj)
{
    _s32_div_f((u32)*(u8 *)(obj + 0x2c63) << 0xc, 100);
}
