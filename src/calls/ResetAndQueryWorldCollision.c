#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern void func_020351cc(CollisionWorld *world, void *query);
extern CollisionWorld *gActorRegistry;

void ResetAndQueryWorldCollision(void *query)
{
    func_020351cc(gActorRegistry, query);
}
