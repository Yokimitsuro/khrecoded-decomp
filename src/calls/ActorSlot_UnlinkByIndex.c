#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void func_02035c5c(ActorSlot *slot);
extern ActorRegistry *data_0206083c;

void ActorSlot_UnlinkByIndex(int index)
{
    func_02035c5c(data_0206083c->slots[index]);
}
