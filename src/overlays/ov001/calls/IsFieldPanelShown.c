#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x47C];
    s32 panelState;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

BOOL IsFieldPanelShown(void)
{
    if (data_ov001_020a04c4.manager->panelState == 2) {
        return TRUE;
    }
    return FALSE;
}
