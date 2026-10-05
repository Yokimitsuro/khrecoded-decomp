#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x60c];
    int slotValues[2];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

int GetFieldSlotValue(int index)
{
    if (index < 0 || index > 1) {
        return -1;
    }
    return data_ov001_020a04c4.manager->slotValues[index];
}
