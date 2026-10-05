#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap();
extern void InitTextLayerAt();
extern void func_ov015_02079bc0();
extern void FlushBufferAndRunCallback();
extern u32 CallIndexedHandler();
extern void FillBackgroundLayerRect();

/* Allocates and registers a tiled graphics object. */
void *CreateTileObject(u32 ownerId, u32 value, u16 *layout, void *tileData, void *mapData) {
    void *context;
    u32 id;

    context = NNSi_FndAllocFromDefaultHeap(0x34);
    InitTextLayerAt(context, ownerId, 0, value, layout);
    func_ov015_02079bc0(context, layout, tileData, mapData);
    FlushBufferAndRunCallback(context);
    id = CallIndexedHandler(ownerId);
    FillBackgroundLayerRect(context, id, layout[0], layout[1], layout[5] & 0xff);
    return context;
}
