#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern ActorSlot *Obj_SetWord1CC(ActorSlot *slot, u32 value);
extern ActorRegistry *data_0206083c;

ActorSlot *ActorSlot_SetField1CCByIndex(int index, u32 value)
{
    return Obj_SetWord1CC(data_0206083c->slots[index], value);
}
