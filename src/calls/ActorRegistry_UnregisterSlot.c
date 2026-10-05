#include "src/calls/actor_registry.h"

ActorSlot *ActorRegistry_UnregisterSlot(ActorSlot *slot, int index)
{
    gActorRegistry->slots[index] = NULL;
    slot->flags &= 0xff7f;
    return slot;
}
