#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18de6];
    u16 slotCount;
} StageManager;

typedef struct {
    u8 pad_00[8];
    s8 currentValue;
    u8 pad_09[6];
    s8 defaultValue;
} StageSlot;

extern StageManager *data_ov001_020a0528;
extern StageSlot *GetStageObjectHandle(u32 id);

void RestoreStageSlotDefault(u32 index)
{
    StageSlot *slot;

    if (index < data_ov001_020a0528->slotCount) {
        slot = GetStageObjectHandle((index + 1) & 0xffff);
        if (slot != NULL) {
            slot->currentValue = slot->defaultValue;
        }
    }
}
