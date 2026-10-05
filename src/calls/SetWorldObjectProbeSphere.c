#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldObject WorldObject;

typedef struct CollisionWorld {
    u8 pad_00[0x20];
    WorldObject *objects[1];
} CollisionWorld;

extern void func_020361cc(WorldObject *object, BOOL enable, fx32 radius);
extern CollisionWorld *data_0206083c;

void SetWorldObjectProbeSphere(int index, BOOL enable, fx32 radius)
{
    func_020361cc(data_0206083c->objects[index], enable, radius);
}
