#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void ActorSlot_Unlink(ActorSlot *slot);
extern ActorRegistry *data_0206083c;

void ActorSlot_UnlinkByIndex(int index)
{
    ActorSlot_Unlink(data_0206083c->slots[index]);
}
