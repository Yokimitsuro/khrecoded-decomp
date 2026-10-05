#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollShape {
    u8 pad_00[0x1c];
    int kind;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} CollShape;

typedef struct FieldActor {
    u8 pad_00[0x130];
    CollShape shape;
} FieldActor;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 slot;
    u8 pad_33[0x17];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
} FieldObject;

typedef int (*TouchFn)(CollShape *self, CollShape *other, void *context, int flags);
typedef int (*ResolveFn)(CollShape *self, CollShape *other, void *context, int flags, VecFx32 *push);

extern TouchFn gCollisionTestPairDispatch[][6];
extern ResolveFn gCollisionSweepPairDispatch[][6];
extern FieldActor *ActorRegistry_GetEntityByIndex(int slot);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int CollideFieldObjectActor(FieldObject *object, CollShape *other, void *context)
{
    VecFx32 relative;
    VecFx32 push;
    FieldActor *actor;
    int result;

    if (object->flags & 2) {
        return 0;
    }
    actor = ActorRegistry_GetEntityByIndex(object->slot);
    if (object->state == 0) {
        if (actor->shape.max.x >= other->min.x && actor->shape.min.x <= other->max.x && actor->shape.max.z >= other->min.z &&
            actor->shape.min.z <= other->max.z && actor->shape.max.y >= other->min.y && actor->shape.min.y <= other->max.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                if (actor->shape.velocity.x == 0 && actor->shape.velocity.y == 0 && actor->shape.velocity.z == 0) {
                    result = 2;
                } else {
                    push = actor->shape.velocity;
                    result = 1;
                }
            } else {
                VEC_Subtract(&actor->shape.velocity, &other->velocity, &relative);
                push = relative;
                if (push.x == 0 && push.y == 0 && push.z == 0) {
                    result = 2;
                } else {
                    result = 1;
                }
            }
        } else {
            result = 0;
        }
        if (result != 0) {
            if (result == 2) {
                return gCollisionTestPairDispatch[actor->shape.kind][other->kind](&actor->shape, other, context, 0xe);
            }
            return gCollisionSweepPairDispatch[actor->shape.kind][other->kind](&actor->shape, other, context, 0xc, &push);
        }
        return 0;
    }
    return 0;
}
