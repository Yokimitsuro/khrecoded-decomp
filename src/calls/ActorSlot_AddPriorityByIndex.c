#include "src/calls/actor_registry.h"

u32 ActorSlot_AddPriorityByIndex(int index, u32 amount)
{
    u32 delta = amount & 0xff;
    ActorSlot *slot = gActorRegistry->slots[index];
    u32 result = slot->priority + delta;
    slot->priority = result;
    return result;
}
