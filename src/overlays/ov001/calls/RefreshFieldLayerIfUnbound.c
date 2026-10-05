#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x450];
    void *layerScreens[3];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern int func_ov027_020b9e10(FieldManager *manager, int layer);

void RefreshFieldLayerIfUnbound(int layer)
{
    void *screen = NULL;

    switch (layer) {
    case 9:
        screen = data_ov001_020a04c4.manager->layerScreens[0];
        break;
    case 10:
        screen = data_ov001_020a04c4.manager->layerScreens[1];
        break;
    case 11:
        screen = data_ov001_020a04c4.manager->layerScreens[2];
        break;
    }
    if (screen == NULL) {
        func_ov027_020b9e10(data_ov001_020a04c4.manager, layer);
    }
}
