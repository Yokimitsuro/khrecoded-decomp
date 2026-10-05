#include "src/calls/actor_registry.h"

void *ActorRegistry_GetEntityByIndex(int index)
{
    return (u8 *)gActorRegistry->slots[index] + 0x10;
}
