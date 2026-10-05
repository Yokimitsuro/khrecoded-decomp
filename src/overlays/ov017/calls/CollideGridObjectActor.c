#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollShape {
    u8 pad_00[0x1c];
    int kind;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} CollShape;

typedef struct BoxShape {
    u8 pad_00[4];
    VecFx32 max;
    VecFx32 min;
    int kind;
} BoxShape;

typedef struct GridActor {
    u8 pad_00[0x130];
    BoxShape box;
} GridActor;

typedef struct GridObject {
    u8 pad_00[0x2c];
    int shapeKind;
    u8 pad_30[2];
    u8 slot;
    u8 pad_33[0x15];
    s8 state;
} GridObject;

typedef int (*TouchFn)(BoxShape *self, CollShape *other, void *context, int flags);
typedef int (*ResolveFn)(BoxShape *self, CollShape *other, void *context, int flags, VecFx32 *push);

extern TouchFn gCollisionTestPairDispatch[][6];
extern ResolveFn gCollisionSweepPairDispatch[][6];
extern GridActor *ActorRegistry_GetEntityByIndex(int slot);
extern void NegateVecFx32(VecFx32 *vec);

int CollideGridObjectActor(GridObject *object, CollShape *other, void *context)
{
    VecFx32 reverse;
    VecFx32 push;
    GridActor *actor;
    int result;

    if (object->shapeKind >= 0 && object->state == 0) {
        actor = ActorRegistry_GetEntityByIndex(object->slot);
        if (actor->box.max.x >= other->min.x && actor->box.min.x <= other->max.x && actor->box.max.z >= other->min.z &&
            actor->box.min.z <= other->max.z && actor->box.max.y >= other->min.y && actor->box.min.y <= other->max.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                result = 2;
            } else {
                reverse = other->velocity;
                NegateVecFx32(&reverse);
                push = reverse;
                result = 1;
            }
        } else {
            result = 0;
        }
        if (result != 0) {
            if (result == 2) {
                return gCollisionTestPairDispatch[actor->box.kind][other->kind](&actor->box, other, context, (other->kind == 2 ? 2 : 0) | 8);
            }
            return gCollisionSweepPairDispatch[actor->box.kind][other->kind](&actor->box, other, context, 8, &push);
        }
        return 0;
    }
    return 0;
}
