#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_01ffce6c(CollisionWorld *world, void *query);
extern CollisionWorld *data_0206083c;

CollisionResult *QueryWorldMotionCollision(void *query)
{
    return func_01ffce6c(data_0206083c, query);
}
