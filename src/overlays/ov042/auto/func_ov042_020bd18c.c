#include "nitro/types.h"

extern u8 *data_ov042_020be5e0;

u32 func_ov042_020bd18c(void)
{
    return *(const u32 *)(data_ov042_020be5e0 + 0x40);
}
