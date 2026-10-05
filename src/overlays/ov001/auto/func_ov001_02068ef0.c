#include "nitro/types.h"

extern u8 *data_ov001_020a0494;

void func_ov001_02068ef0(u16 value)
{
    *(u16 *)(data_ov001_020a0494 + 0x22) = value;
}
