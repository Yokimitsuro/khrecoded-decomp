#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor {
    u8 pad_000[0x95c];
    fx32 countdown;
} Actor;

void Actor_ExtendCountdown(Actor *actor, fx32 duration)
{
    if (actor->countdown < duration) {
        actor->countdown = duration;
    }
}
