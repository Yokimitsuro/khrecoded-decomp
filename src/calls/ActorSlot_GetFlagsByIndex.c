#include "src/calls/actor_registry.h"

u16 ActorSlot_GetFlagsByIndex(int index)
{
    return gActorRegistry->slots[index]->flags;
}
