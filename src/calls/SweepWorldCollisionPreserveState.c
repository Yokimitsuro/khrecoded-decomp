#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;
typedef struct CollisionResult CollisionResult;

extern CollisionResult *PXI_Init_02035278(CollisionWorld *world, void *params);
extern CollisionWorld *gActorRegistry;

CollisionResult *SweepWorldCollisionPreserveState(void *params)
{
    return PXI_Init_02035278(gActorRegistry, params);
}
