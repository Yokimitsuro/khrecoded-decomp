#include "nitro/types.h"

extern u8 *data_ov030_020bd020;

u8 func_ov030_020bb388(void)
{
    return *(const u8 *)(data_ov030_020bd020 + 0x9);
}
