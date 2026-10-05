#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void TestQueryAgainstMeshList(CollisionWorld *world, void *params);
extern CollisionWorld *gActorRegistry;

void TestQueryAgainstWorldMeshes(void *params)
{
    TestQueryAgainstMeshList(gActorRegistry, params);
}
