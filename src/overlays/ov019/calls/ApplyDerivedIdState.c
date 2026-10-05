#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x32];
    u8 idByte;
} Actor;

extern u32 ActorSlot_IsFlag8SetByIndex(u8 id);
extern void CacheEntry_SetActive(Actor *self, u32 value);

void
ApplyDerivedIdState(Actor *self)
{
    u32 value = ActorSlot_IsFlag8SetByIndex(self->idByte);
    CacheEntry_SetActive(self, value);
}
