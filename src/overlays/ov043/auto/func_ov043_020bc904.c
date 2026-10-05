#include "nitro/types.h"

extern u8 *data_ov043_020bd2e0;

void func_ov043_020bc904(u32 value)
{
    *(u32 *)(data_ov043_020bd2e0 + 0x38) = value;
}
