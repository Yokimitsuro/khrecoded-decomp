#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ModeLayer;

typedef struct {
    s32 layerCount;
    u8 pad_04[0xc];
    ModeLayer *layers;
} ModeLayerSet;

typedef struct {
    u8 pad_00[0x54];
    ModeLayerSet layerSet;
} ModeState;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void FlushBufferAndRunCallback(void *context);
extern BOOL DestroyFndObjectList(void *container);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeModeLayerArray(ModeState *state)
{
    ModeLayerSet *set = &state->layerSet;

    if (set->layers != NULL) {
        int index;

        for (index = 0; index < set->layerCount; index++) {
            ModeLayer *layers = set->layers;

            CallVirtualHandlerSlot1(&layers[index], 0);
            FlushBufferAndRunCallback(&layers[index]);
            DestroyFndObjectList(&layers[index]);
        }
        NNSi_FndFreeFromDefaultHeap(set->layers);
        set->layers = NULL;
        set->layerCount = 0;
    }
}
