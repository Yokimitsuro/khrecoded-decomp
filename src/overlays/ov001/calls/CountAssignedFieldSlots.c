#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x60C];
    s32 slotValues[2];
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

int CountAssignedFieldSlots(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    int slot;

    for (slot = 0; slot < 2; slot++) {
        if (manager->slotValues[slot] == -1) {
            return slot;
        }
    }
    return slot;
}
