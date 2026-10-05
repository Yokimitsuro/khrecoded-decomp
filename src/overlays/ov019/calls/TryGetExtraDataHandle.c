#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x68];
    u32 extraHandle;
} Actor;

BOOL
TryGetExtraDataHandle(Actor *self, u32 *out)
{
    u32 handle = self->extraHandle;
    out[0] = 0;
    out[1] = handle;
    out[2] = 0;
    return self->extraHandle != 0;
}
