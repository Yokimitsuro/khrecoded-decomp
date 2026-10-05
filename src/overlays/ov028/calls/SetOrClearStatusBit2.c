#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;

void SetOrClearStatusBit2(s32 enable)
{
    if (enable != 0) {
        *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 4;
        return;
    }
    *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) & 0xfffb;
}
