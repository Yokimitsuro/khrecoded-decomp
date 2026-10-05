#include "nitro/types.h"

extern u8 *data_ov042_020be5e0;

void func_ov042_020bd5f4(u32 value)
{
    *(u32 *)(data_ov042_020be5e0 + 0x48) = value;
}
