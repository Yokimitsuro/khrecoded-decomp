#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void ActorSlot_SetFlag8(ActorSlot *slot, BOOL enable);
extern ActorRegistry *gActorRegistry;

void ActorSlot_SetFlag8ByIndex(int index, BOOL enable)
{
    ActorSlot_SetFlag8(gActorRegistry->slots[index], enable);
}
