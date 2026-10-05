#include "nitro/types.h"

typedef struct CollisionBody CollisionBody;
typedef struct CollisionHit CollisionHit;

extern BOOL func_020405c8(CollisionBody *bodyA, CollisionBody *bodyB, CollisionHit *hit, u32 flags);

BOOL TestCapsuleAgainstCapsuleSwapped(CollisionBody *bodyA, CollisionBody *bodyB, CollisionHit *hit, u32 flags)
{
    return func_020405c8(bodyB, bodyA, hit, flags ^ 1);
}
