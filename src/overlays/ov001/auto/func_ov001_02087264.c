#include "nitro/types.h"

extern u8 *data_ov001_020a04fc;

u32 func_ov001_02087264(void)
{
    return *(const u32 *)(data_ov001_020a04fc + 0x8);
}
