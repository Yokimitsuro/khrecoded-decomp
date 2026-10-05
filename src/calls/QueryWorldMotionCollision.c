#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_01ffce6c(CollisionWorld *world, void *query);
extern CollisionWorld *gActorRegistry;

CollisionResult *QueryWorldMotionCollision(void *query)
{
    return func_01ffce6c(gActorRegistry, query);
}
