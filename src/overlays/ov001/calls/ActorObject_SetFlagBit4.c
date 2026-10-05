#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xef4];
    u32 flags;
} Actor;

void ActorObject_SetFlagBit4(Actor *actor, int enable)
{
    if (enable != 0) {
        actor->flags = actor->flags | 0x10;
        return;
    }
    actor->flags = actor->flags & 0xffffffef;
}
