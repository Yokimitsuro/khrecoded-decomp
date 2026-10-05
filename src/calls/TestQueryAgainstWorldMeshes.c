#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void func_02035284(CollisionWorld *world, void *params);
extern CollisionWorld *data_0206083c;

void TestQueryAgainstWorldMeshes(void *params)
{
    func_02035284(data_0206083c, params);
}
