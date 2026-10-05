#include "nitro/types.h"

extern u8 *data_ov001_020a04fc;

u32 func_ov001_020870e4(void)
{
    return *(const u8 *)(data_ov001_020a04fc + 0x5) & 0x11;
}
