#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[4];
    u8 clearRegion[0xc];
    u8 pad_010[0xEE4];
    u32 flags;
} Actor;

extern void MI_CpuFill8(void *dst, int val, u32 size);

void ClearActorTimerFields(Actor *actor)
{
    actor->flags = actor->flags & 0xfffffe7f;
    MI_CpuFill8(actor->clearRegion, 0, 0xc);
}
