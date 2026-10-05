#include "nitro/types.h"

typedef struct StageObject {
    u8 pad0[6];
    u16 flags;
    u8 pad8[0x1c0];
} StageObject;

typedef struct StageManager {
    u8 pad_00000[0x210];
    StageObject *objects;
    u8 pad_00214[0x18bd2];
    u16 slotCount;
} StageManager;

typedef struct StageSlot {
    u8 pad_00[0xa];
    s16 firstObject;
    s16 lastObject;
} StageSlot;

extern StageManager *data_ov001_020a0528;
extern StageSlot *GetStageObjectHandle(u32 id);
extern void func_ov001_0209b520(u32 index, u32 mask);

void LockStageSlotObjects(u32 index) {
    int i;
    StageSlot *slot;

    if (index < data_ov001_020a0528->slotCount) {
        slot = GetStageObjectHandle((u16)(index + 1));
        if (slot != NULL) {
            for (i = slot->firstObject; i <= slot->lastObject; i++) {
                data_ov001_020a0528->objects[i].flags |= 0x2000;
            }
            func_ov001_0209b520(index, 1);
        }
    }
}
