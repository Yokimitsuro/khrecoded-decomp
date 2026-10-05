#include "nitro/types.h"

typedef unsigned int UNDEF4;

typedef struct Actor {
    u8 pad_000[0x894];
    u8 animState[1];
} Actor;

extern void ActorAnim_AdvanceAndGetRootDelta(void *request, void *animState);
extern void Actor_FireExpiredTrackCues(Actor *actor);

void QueueActorAnimEvent(Actor *actor, UNDEF4 param2, UNDEF4 param3, UNDEF4 param4)
{
    u8 stackBuffer[0xc];
    UNDEF4 stackValue;

    stackValue = param4;
    ActorAnim_AdvanceAndGetRootDelta(stackBuffer, actor->animState);
    Actor_FireExpiredTrackCues(actor);
}
