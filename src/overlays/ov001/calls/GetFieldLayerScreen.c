#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x450];
    void *layerScreens[3];
    u8 pad_45C[0x47c - 0x45c];
    s32 panelState;
    u32 unk_480_0 : 9;
    u32 splitScreenMode : 1;
    u32 unk_480_10 : 22;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

void *GetFieldLayerScreen(s32 layer)
{
    void *screen = NULL;
    FieldManager *manager = data_ov001_020a04c4.manager;

    if ((manager->panelState != 0 && manager->panelState != 3) || manager->splitScreenMode == 1) {
        switch (layer) {
        case 9:
            screen = manager->layerScreens[0];
            break;
        case 10:
            screen = manager->layerScreens[1];
            break;
        case 11:
            screen = manager->layerScreens[2];
            break;
        }
    }
    return screen;
}
