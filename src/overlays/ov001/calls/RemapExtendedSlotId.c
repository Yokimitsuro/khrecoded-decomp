#include "nitro/types.h"

extern s8 data_ov001_020a038c[];

u16 RemapExtendedSlotId(u16 slotId)
{
    if (slotId >= 0x46) {
        s8 mapped = data_ov001_020a038c[(s8)(slotId - 0x46)];

        if (mapped < 0) {
            slotId -= 0x46;
        } else {
            slotId = mapped;
        }
    }
    return slotId;
}
