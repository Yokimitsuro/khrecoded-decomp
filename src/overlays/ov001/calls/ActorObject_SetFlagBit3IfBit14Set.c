#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xef4];
    u32 flags;
} Actor;

void ActorObject_SetFlagBit3IfBit14Set(Actor *actor, int enable)
{
    u32 flags = actor->flags;
    if ((flags & 0x4000) != 0) {
        if (enable != 0) {
            actor->flags = flags | 8;
            return;
        }
        actor->flags = flags & 0xfffffff7;
    }
}
