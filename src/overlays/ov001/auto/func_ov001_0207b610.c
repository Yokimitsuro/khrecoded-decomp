#include "nitro/types.h"

extern u8 *data_ov001_020a04e8;

u32 func_ov001_0207b610(void)
{
    return *(const u32 *)(data_ov001_020a04e8 + 0x38);
}
