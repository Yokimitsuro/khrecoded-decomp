#include "nitro/types.h"

extern u8 *data_ov001_020a04f8;

u32 func_ov001_0207f0b4(void)
{
    return *(const u32 *)(data_ov001_020a04f8 + 0x8);
}
