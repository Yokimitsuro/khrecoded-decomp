#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x42c];
    void *overlayScreen;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

BOOL HasFieldOverlayScreen(void)
{
    if (data_ov001_020a04c4.manager->overlayScreen != NULL) {
        return TRUE;
    }
    return FALSE;
}
