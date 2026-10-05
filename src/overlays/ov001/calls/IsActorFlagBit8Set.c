#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEF4];
    u32 flags;
} Actor;

BOOL IsActorFlagBit8Set(Actor *actor)
{
    if ((actor->flags & 8) != 0) {
        return TRUE;
    }
    return FALSE;
}
