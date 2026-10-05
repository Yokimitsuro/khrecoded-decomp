#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *func_020351e0(CollisionWorld *world, void *params);
extern CollisionWorld *data_0206083c;

CollisionResult *SweepWorldCollision(void *params)
{
    return func_020351e0(data_0206083c, params);
}
