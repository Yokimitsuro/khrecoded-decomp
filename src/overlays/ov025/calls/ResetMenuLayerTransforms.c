#include "nitro/types.h"

typedef void (*LayerScaleFunc)(int layer, int offset, int scale);

typedef struct LayerIdPair {
    int ids[2];
} LayerIdPair;

typedef struct LayerFuncPair {
    LayerScaleFunc funcs[2];
} LayerFuncPair;

extern u32 data_ov025_020b7780;
extern LayerIdPair data_ov025_020b76a0;
extern LayerFuncPair gSubBgScreenLoaders;
extern int func_ov027_020b9e10(int owner, int layerId);

void ResetMenuLayerTransforms(void)
{
    LayerIdPair layerIds = data_ov025_020b76a0;
    LayerFuncPair applyFuncs = gSubBgScreenLoaders;
    u32 menu = data_ov025_020b7780;
    u32 i;

    if (menu != 0 && *(int *)(menu + 0x64e4) != 0) {
        for (i = 0; i < 2; i++) {
            int layer = func_ov027_020b9e10(menu + 0x64c8, layerIds.ids[i]);
            applyFuncs.funcs[i](layer, 0, 0x1000);
        }
    }
}
