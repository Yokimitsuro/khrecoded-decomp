#include "nitro/types.h"

extern u8 *data_ov001_020a0494;

void func_ov001_02068ec4(u32 value)
{
    *(u32 *)(data_ov001_020a0494 + 0x8) = value;
}
