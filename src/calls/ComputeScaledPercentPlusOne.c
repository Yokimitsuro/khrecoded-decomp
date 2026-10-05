#include "nitro/types.h"

extern u8 *data_0205fe0c;
extern s32 _s32_div_f(s32 numerator, s32 denominator);

int ComputeScaledPercentPlusOne(void)
{
    s32 result = _s32_div_f((u32)*(u8 *)(data_0205fe0c + 0x2c65) * 0xf000, 0x5a);
    return result + 0x1000;
}
