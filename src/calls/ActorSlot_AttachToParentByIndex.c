#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void ActorSlot_AttachToParent(ActorSlot *child, ActorSlot *parent, void *initializationData);
extern ActorRegistry *gActorRegistry;

void ActorSlot_AttachToParentByIndex(int childIndex, int parentIndex, void *initializationData)
{
    ActorSlot_AttachToParent(gActorRegistry->slots[childIndex],
                                      gActorRegistry->slots[parentIndex], initializationData);
}
