#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x474];
    s16 paletteSlot;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

s32 GetClampedPaletteSlot(void)
{
    s32 slot = data_ov001_020a04c4.manager->paletteSlot;

    if (slot > 3) {
        return 3;
    }
    if (slot < 0) {
        return 0;
    }
    return slot;
}
