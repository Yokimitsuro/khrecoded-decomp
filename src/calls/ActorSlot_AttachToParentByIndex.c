#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void func_02035b88(ActorSlot *child, ActorSlot *parent, void *initializationData);
extern ActorRegistry *data_0206083c;

void ActorSlot_AttachToParentByIndex(int childIndex, int parentIndex, void *initializationData)
{
    func_02035b88(data_0206083c->slots[childIndex],
                                      data_0206083c->slots[parentIndex], initializationData);
}
