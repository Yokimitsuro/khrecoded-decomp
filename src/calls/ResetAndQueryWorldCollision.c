#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void func_020351cc(CollisionWorld *world, void *query);
extern CollisionWorld *data_0206083c;

void ResetAndQueryWorldCollision(void *query)
{
    func_020351cc(data_0206083c, query);
}
