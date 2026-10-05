#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEF4];
    u32 flags;
} Actor;

void SetActorFlagBit4(Actor *actor, s32 enable)
{
    if (enable != 0) {
        actor->flags = actor->flags | 4;
        return;
    }
    actor->flags = actor->flags & 0xfffffffb;
}
