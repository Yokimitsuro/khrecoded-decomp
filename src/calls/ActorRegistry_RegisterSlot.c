#include "src/calls/actor_registry.h"

ActorSlot *ActorRegistry_RegisterSlot(ActorSlot *slot, int index)
{
    gActorRegistry->slots[index] = slot;
    slot->flags |= 0x80;
    return slot;
}
