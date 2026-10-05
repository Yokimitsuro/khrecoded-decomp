#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xd];
    u8 validSlotCount;
} SaveSelectScreen;

extern SaveSelectScreen *data_ov080_020c5e20;

void UpdateValidSlotCount(u32 *slotCount)
{
    if (data_ov080_020c5e20 != NULL && data_ov080_020c5e20->validSlotCount != *slotCount) {
        *slotCount = data_ov080_020c5e20->validSlotCount;
    }
}
