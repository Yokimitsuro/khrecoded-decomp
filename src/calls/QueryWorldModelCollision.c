#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *QueryModelCollision(CollisionWorld *world, void *query);
extern CollisionWorld *gActorRegistry;

CollisionResult *QueryWorldModelCollision(void *query)
{
    return QueryModelCollision(gActorRegistry, query);
}
