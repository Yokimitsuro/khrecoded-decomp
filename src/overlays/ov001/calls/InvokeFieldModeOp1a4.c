#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x2f4];
    u8 modeState[4];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern void data_ov041_020cf1c4(void *state, int value);

void InvokeFieldModeOp1a4(int value)
{
    data_ov041_020cf1c4(data_ov001_020a04c4.manager->modeState, value);
}

