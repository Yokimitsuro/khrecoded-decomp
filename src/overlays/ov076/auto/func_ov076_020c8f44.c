#include "nitro/types.h"

extern u8 *data_ov076_020cd400;

u32 func_ov076_020c8f44(void)
{
    return *(const u32 *)(data_ov076_020cd400 + 0x28);
}
