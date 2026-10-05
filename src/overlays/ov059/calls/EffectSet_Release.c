#pragma opt_propagation off
#include "nitro/types.h"

typedef struct {
    u8 data[0x104];
} ResourceSlot;

typedef struct {
    u8 pad_00[0x3c];
    void *bufferA;
    void *bufferB;
    u8 pad_44[4];
    ResourceSlot slots[6];
} EffectSet;

extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void ReleaseResourceAndDetach(ResourceSlot *slot);
extern void ReleaseCallbackOwnedBuffer(EffectSet *set);

void EffectSet_Release(EffectSet *set)
{
    int i;

    NNSi_FndFreeFromDefaultHeap(set->bufferA);
    NNSi_FndFreeFromDefaultHeap(set->bufferB);
    for (i = 0; i < 6; i++) {
        ReleaseResourceAndDetach(&set->slots[i]);
    }
    ReleaseCallbackOwnedBuffer(set);
}
