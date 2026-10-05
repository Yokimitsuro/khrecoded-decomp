#include "nitro/types.h"

extern u8 *data_ov030_020bd020;

u32 func_ov030_020bb230(void)
{
    return *(const u16 *)(data_ov030_020bd020 + 0x6) & 0x60;
}
