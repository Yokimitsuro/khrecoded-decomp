#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_01ffce24(CollisionWorld *world, void *query);
extern CollisionWorld *gActorRegistry;

CollisionResult *QueryWorldModelCollision(void *query)
{
    return func_01ffce24(gActorRegistry, query);
}
