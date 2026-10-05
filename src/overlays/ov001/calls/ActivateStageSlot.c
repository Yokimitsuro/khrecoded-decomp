#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18de6];
    u16 slotCount;
} StageManager;

typedef struct {
    u8 pad_00[9];
    u8 active : 1;
    u8 pending : 1;
} StageSlot;

extern StageManager *data_ov001_020a0528;
extern StageSlot *GetStageObjectHandle(u32 id);

void ActivateStageSlot(u32 index)
{
    StageSlot *slot;

    if (index < data_ov001_020a0528->slotCount) {
        slot = GetStageObjectHandle((index + 1) & 0xffff);
        slot->active = 1;
        slot->pending = 0;
    }
}
