#include "nitro/types.h"

extern u32 data_ov044_020d0ec0;

void SetPanelFlagBit1(BOOL enable)
{
    u32 panel = data_ov044_020d0ec0;

    if (enable) {
        *(u32 *)(panel + 0x38) |= 2;
    } else {
        *(u32 *)(panel + 0x38) &= ~2;
    }
}
