#include "nitro/types.h"

extern u8 *data_ov035_020bc500;

u32 func_ov035_020baa38(void)
{
    return *(const u16 *)(data_ov035_020bc500 + 0x6) & 0x20;
}
