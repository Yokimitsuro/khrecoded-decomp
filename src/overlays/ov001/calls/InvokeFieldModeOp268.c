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
extern void data_ov041_020cf288(void *state);

void InvokeFieldModeOp268(void)
{
    data_ov041_020cf288(data_ov001_020a04c4.manager->modeState);
}

