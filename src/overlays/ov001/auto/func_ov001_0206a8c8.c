#include "nitro/types.h"

extern u8 *data_ov001_020a04a0;

void func_ov001_0206a8c8(u32 value)
{
    *(u32 *)(data_ov001_020a04a0 + 0x1c) = value;
}
