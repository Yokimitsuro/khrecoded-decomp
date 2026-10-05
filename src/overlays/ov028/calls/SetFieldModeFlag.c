#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;

void SetFieldModeFlag(u8 mode)
{
    *(u8 *)(data_ov028_020bb3a0 + 8) = mode;
    *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x4000;
}
