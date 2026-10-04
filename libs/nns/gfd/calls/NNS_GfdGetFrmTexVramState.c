typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL active;
    const BOOL halfSize;
    const unsigned short index;
    const unsigned short padding;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;

typedef struct NNSGfdFrmTexVramState {
    u32 address[10];
} NNSGfdFrmTexVramState;

extern NNSGfdFrmTexRegionState sFrmTexVramRegions[5];

void NNS_GfdGetFrmTexVramState(NNSGfdFrmTexVramState *state)
{
    int i;

    for (i = 0; i < 5; i++) {
        state->address[i * 2] = sFrmTexVramRegions[i].head;
        state->address[i * 2 + 1] = sFrmTexVramRegions[i].tail;
    }
}
