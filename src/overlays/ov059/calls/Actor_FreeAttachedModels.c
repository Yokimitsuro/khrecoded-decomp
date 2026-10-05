#include "nitro/types.h"

typedef struct AttachedModel {
    u8 data[0x104];
} AttachedModel;

typedef struct Actor {
    u8 pad_0000[0x1700];
    AttachedModel *attachedModels;
} Actor;

extern void ReleaseResourceAndDetach(AttachedModel *model);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void Actor_FreeAttachedModels(Actor *actor)
{
    int i;

    for (i = 0; i < 4; i++) {
        ReleaseResourceAndDetach(&actor->attachedModels[i]);
    }
    NNSi_FndFreeFromDefaultHeap(actor->attachedModels);
}
