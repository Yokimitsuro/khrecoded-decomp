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
extern char data_ov041_020cf1f8[];

void InvokeFieldModeOp1d8(void)
{
    ((void (*)(void *))data_ov041_020cf1f8)(data_ov001_020a04c4.manager->modeState);
}

