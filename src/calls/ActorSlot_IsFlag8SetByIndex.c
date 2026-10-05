#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern BOOL Container_HasFlag3(ActorSlot *slot);
extern ActorRegistry *gActorRegistry;

BOOL ActorSlot_IsFlag8SetByIndex(int index)
{
    return Container_HasFlag3(gActorRegistry->slots[index]);
}
