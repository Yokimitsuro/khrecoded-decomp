#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x5a];
    u16 flags;
} Actor;

BOOL
IsDestroyed(Actor *self)
{
    return (self->flags & 0x8000) != 0;
}
