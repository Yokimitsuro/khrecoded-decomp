#include "nitro/types.h"

typedef struct ActorExtraSlot {
    u8 data[0xc];
} ActorExtraSlot;

typedef struct Actor {
    u8 pad_000[0x870];
    ActorExtraSlot extraSlots[3];
} Actor;

extern void MI_CpuFill8(void *dest, int value, u32 size);

void ActorObject_ClearExtraSlot(Actor *actor, int index)
{
    MI_CpuFill8(&actor->extraSlots[index], 0, sizeof(ActorExtraSlot));
}
