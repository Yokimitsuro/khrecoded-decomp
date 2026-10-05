#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *PXI_Init_02035278(CollisionWorld *world, void *params);
extern CollisionWorld *data_0206083c;

CollisionResult *SweepWorldCollisionPreserveState(void *params)
{
    return PXI_Init_02035278(data_0206083c, params);
}
