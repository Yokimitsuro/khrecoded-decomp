#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void TestQueryAgainstMeshList(CollisionWorld *world, void *params);
extern CollisionWorld *data_0206083c;

void TestQueryAgainstWorldMeshes(void *params)
{
    TestQueryAgainstMeshList(data_0206083c, params);
}
