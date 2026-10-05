#include "nitro/types.h"

typedef void (*LayerLoadFunc)(const void *src, u32 offset, u32 size);

typedef struct {
    int ids[4];
} LayerIdSet4;

typedef struct {
    LayerLoadFunc loaders[4];
} LayerLoaderSet4;

extern const LayerIdSet4 data_ov039_020be760;
extern const LayerLoaderSet4 gOv039SubBgScreenLoaders;
extern int data_ov039_020bea20;
extern void func_ov027_020b9d68(int layers, int id);
extern int func_ov027_020b9e10(int layers, int id);

void LoadBgLayerSet4(void)
{
    LayerIdSet4 idSet = data_ov039_020be760;
    LayerLoaderSet4 loaderSet = gOv039SubBgScreenLoaders;
    u32 i;

    for (i = 0; i < 4; i++) {
        int id = idSet.ids[i];
        int base;
        int layer;

        func_ov027_020b9d68(data_ov039_020bea20 + 0xc9a0, id);
        base = data_ov039_020bea20;
        layer = func_ov027_020b9e10(base + 0xc9a0, id);
        loaderSet.loaders[i]((const void *)layer, 0, *(u16 *)(base + 0xc9ac) << 1);
    }
}
