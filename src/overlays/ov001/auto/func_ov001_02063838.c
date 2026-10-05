#include "nitro/types.h"

extern u8 *data_ov001_020a0480;

u32 func_ov001_02063838(void)
{
    return *(const u32 *)(data_ov001_020a0480 + 0x20) & 0x20;
}
