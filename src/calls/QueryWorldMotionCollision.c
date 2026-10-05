#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *QueryModelMotionCollision(CollisionWorld *world, void *query);
extern CollisionWorld *gActorRegistry;

CollisionResult *QueryWorldMotionCollision(void *query)
{
    return QueryModelMotionCollision(gActorRegistry, query);
}
