#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x818];
    u32 slotHandler;
    u32 slotArg;
} Actor;

void ActorObject_SetPrimarySlot(Actor *actor, u32 handler, u32 arg)
{
    actor->slotHandler = handler;
    actor->slotArg = arg;
}
