#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ModeLayer;

typedef struct {
    s32 layerCount;
    u8 pad_04[4];
    void **buffers;
    u8 pad_0c[4];
    ModeLayer *layers;
} ModeLayerSet;

typedef struct {
    u8 pad_00[0x38];
    void *workBuffer;
    u8 pad_3c[0x18];
    ModeLayerSet layerSet;
    u8 pad_68[0x2c];
    ModeLayer mainLayer;
} ModeState;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void FlushBufferAndRunCallback(void *context);
extern BOOL DestroyFndObjectList(void *container);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void FreeModeLayerArray(ModeState *state);

void FreeModeResources(ModeState *state)
{
    int index;
    ModeLayerSet *set = &state->layerSet;

    if (state->workBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(state->workBuffer);
        state->workBuffer = NULL;
        CallVirtualHandlerSlot1(&state->mainLayer, 0);
        FlushBufferAndRunCallback(&state->mainLayer);
        DestroyFndObjectList(&state->mainLayer);
    }
    if (set->buffers != NULL) {
        for (index = 0; index < set->layerCount; index++) {
            if (set->buffers[index] != NULL) {
                NNSi_FndFreeFromDefaultHeap(set->buffers[index]);
            }
        }
        NNSi_FndFreeFromDefaultHeap(set->buffers);
        set->buffers = NULL;
    }
    FreeModeLayerArray(state);
}
