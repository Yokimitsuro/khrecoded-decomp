#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEFC];
    u32 field_efc;
} Actor;

void SetActorFieldEfc(Actor *actor, u32 value)
{
    actor->field_efc = value;
}
