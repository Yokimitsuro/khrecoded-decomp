#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern ActorSlot *Obj_SetWord1CC(ActorSlot *slot, u32 value);
extern ActorRegistry *gActorRegistry;

ActorSlot *ActorSlot_SetField1CCByIndex(int index, u32 value)
{
    return Obj_SetWord1CC(gActorRegistry->slots[index], value);
}
