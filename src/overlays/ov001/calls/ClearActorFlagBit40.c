#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEF4];
    u32 flags;
} Actor;

void ClearActorFlagBit40(Actor *actor)
{
    actor->flags = actor->flags & 0xffffffbf;
}
