#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void func_02036154(ActorSlot *slot, BOOL enable);
extern ActorRegistry *gActorRegistry;

void ActorSlot_SetFlag8ByIndex(int index, BOOL enable)
{
    func_02036154(gActorRegistry->slots[index], enable);
}
