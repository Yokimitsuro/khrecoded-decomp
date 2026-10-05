#include "nitro/types.h"

extern s32 FX_Mul(s32 left, s32 right);
extern s32 _s32_div_f(s32 numerator, s32 denominator);

void MultiplyTwoPercentFractions(u8 *obj)
{
    s32 inverseFrac = _s32_div_f((100 - (u32)*(u8 *)(obj + 0x2c65)) * 0x1000, 100);
    s32 directFrac = _s32_div_f((u32)*(u8 *)(obj + 0x2c63) << 0xc, 100);
    FX_Mul(inverseFrac, directFrac);
}
