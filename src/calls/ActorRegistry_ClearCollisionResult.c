#include "src/calls/actor_registry.h"

ActorRegistry *ActorRegistry_ClearCollisionResult(void)
{
    ActorRegistry *registry = gActorRegistry;
    ((ActorRegistryCollisionView *)registry)->collisionResult = NULL;
    return registry;
}
