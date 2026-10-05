#include "nitro/types.h"

typedef void (*LayerLoadFunc)(const void *src, u32 offset, u32 size);

typedef struct {
    int ids[3];
} LayerIdSet3;

typedef struct {
    LayerLoadFunc loaders[3];
} LayerLoaderSet3;

extern const LayerIdSet3 data_ov039_020be754;
extern const LayerLoaderSet3 gMainBgScreenLoaders;
extern int data_ov039_020bea20;
extern void func_ov027_020b9d68(int layers, int id);
extern int func_ov027_020b9e10(int layers, int id);

void LoadBgLayerSet3(void)
{
    LayerIdSet3 idSet = data_ov039_020be754;
    LayerLoaderSet3 loaderSet = gMainBgScreenLoaders;
    u32 i;

    for (i = 0; i < 3; i++) {
        int id = idSet.ids[i];
        int base;
        int layer;

        func_ov027_020b9d68(data_ov039_020bea20 + 0xc9a0, id);
        base = data_ov039_020bea20;
        layer = func_ov027_020b9e10(base + 0xc9a0, id);
        loaderSet.loaders[i]((const void *)layer, 0, *(u16 *)(base + 0xc9ac) << 1);
    }
}
