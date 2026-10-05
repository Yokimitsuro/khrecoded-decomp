#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldObject WorldObject;

typedef struct CollisionWorld {
    u8 pad_00[0x20];
    WorldObject *objects[1];
} CollisionWorld;

extern void func_020361cc(WorldObject *object, BOOL enable, fx32 radius);
extern CollisionWorld *gActorRegistry;

void SetWorldObjectProbeSphere(int index, BOOL enable, fx32 radius)
{
    func_020361cc(gActorRegistry->objects[index], enable, radius);
}
