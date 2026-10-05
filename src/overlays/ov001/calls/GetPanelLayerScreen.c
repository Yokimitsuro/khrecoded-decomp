#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x450];
    void *layerScreens[3];
    u8 pad_45C[0x47c - 0x45c];
    s32 panelState;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

void *GetPanelLayerScreen(s32 layer)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    void *screen = NULL;

    if (manager->panelState != 0 && manager->panelState != 3) {
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
