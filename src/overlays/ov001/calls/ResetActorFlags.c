#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEF4];
    u32 flags;
} Actor;

extern void func_ov001_02088b80(void);

void ResetActorFlags(Actor *actor)
{
    func_ov001_02088b80();
    actor->flags = 0x2000;
}
