#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_01ffce24(CollisionWorld *world, void *query);
extern CollisionWorld *data_0206083c;

CollisionResult *QueryWorldModelCollision(void *query)
{
    return func_01ffce24(data_0206083c, query);
}
