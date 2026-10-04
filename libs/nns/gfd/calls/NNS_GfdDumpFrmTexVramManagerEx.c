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
typedef void (*NNSGfdFrmTexVramDebugDumpCallBack)(int, u32, u32, u32, BOOL, void *);

extern NNSGfdFrmTexRegionState sFrmTexVramRegions[5];

void NNS_GfdDumpFrmTexVramManagerEx(NNSGfdFrmTexVramDebugDumpCallBack callback, void *userContext)
{
    int i;
    const NNSGfdFrmTexRegionState *state = 0;

    for (i = 0; i < 5; i++) {
        state = &sFrmTexVramRegions[i];
        callback(i,
                 state->head + state->baseAddress,
                 state->tail + state->baseAddress,
                 state->halfSize ? 0x10000 : 0x20000,
                 state->active,
                 userContext);
    }
}