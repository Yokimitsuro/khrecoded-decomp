#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *CollWorld_FindHit(CollisionWorld *world, void *params);
extern CollisionWorld *gActorRegistry;

CollisionResult *SweepWorldCollision(void *params)
{
    return CollWorld_FindHit(gActorRegistry, params);
}
