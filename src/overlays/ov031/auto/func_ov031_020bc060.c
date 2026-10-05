#include "nitro/types.h"

extern u8 *data_ov031_020bc820;

u32 func_ov031_020bc060(void)
{
    return *(const u32 *)(data_ov031_020bc820 + 0x30);
}
