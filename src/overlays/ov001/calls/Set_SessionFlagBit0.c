#include "nitro/types.h"

extern u32 data_ov001_020a0480;

void Set_SessionFlagBit0(void)
{
    u8 *flags = (u8 *)(data_ov001_020a0480 + 0x27b6);
    *flags = *flags & ~1 | 1;
}
