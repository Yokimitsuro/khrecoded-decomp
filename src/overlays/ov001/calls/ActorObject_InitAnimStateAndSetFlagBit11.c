#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x894];
    u8 animState[0x660];
    u32 flags;
} Actor;

extern void BindActorAnimation(void *animState);

void ActorObject_InitAnimStateAndSetFlagBit11(Actor *actor)
{
    BindActorAnimation(actor->animState);
    actor->flags = actor->flags | 0x800;
}
