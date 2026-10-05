#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_020351e0(CollisionWorld *world, void *params);
extern CollisionWorld *gActorRegistry;

CollisionResult *SweepWorldCollision(void *params)
{
    return func_020351e0(gActorRegistry, params);
}
