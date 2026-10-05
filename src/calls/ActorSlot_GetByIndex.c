#include "src/calls/actor_registry.h"

ActorSlot *ActorSlot_GetByIndex(int index)
{
    return gActorRegistry->slots[index];
}
