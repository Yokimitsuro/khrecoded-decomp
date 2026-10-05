#include "nitro/types.h"

extern u8 *data_ov001_020a0528;

u8 *GetStagePartySlot(u32 slot)
{
    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    if (slot < 3) {
        return data_ov001_020a0528 + 0x18af4 + slot * 0x2c;
    }
    return 0;
}
