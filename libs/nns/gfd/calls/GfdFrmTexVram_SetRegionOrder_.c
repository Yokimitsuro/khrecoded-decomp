typedef unsigned int u32;
typedef unsigned short u16;
typedef int BOOL;

typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL active;
    const BOOL halfSize;
    const u16 index;
    const u16 padding;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;

typedef struct NNSGfdFrmTexRegionOrder {
    NNSGfdFrmTexRegionState *compressed[2];
    NNSGfdFrmTexRegionState *normal[5];
} NNSGfdFrmTexRegionOrder;

extern NNSGfdFrmTexRegionState sFrmTexVramRegions[5];
extern NNSGfdFrmTexRegionOrder sFrmTexVramRegionOrder;

void GfdFrmTexVram_SetRegionOrder_(int first, int second, int third, int fourth, int fifth)
{
    sFrmTexVramRegionOrder.normal[0] = &sFrmTexVramRegions[first];
    sFrmTexVramRegionOrder.normal[1] = &sFrmTexVramRegions[second];
    sFrmTexVramRegionOrder.normal[2] = &sFrmTexVramRegions[third];
    sFrmTexVramRegionOrder.normal[3] = &sFrmTexVramRegions[fourth];
    sFrmTexVramRegionOrder.normal[4] = &sFrmTexVramRegions[fifth];
}