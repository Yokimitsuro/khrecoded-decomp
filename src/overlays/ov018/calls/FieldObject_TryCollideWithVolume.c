#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitVolume {
    u8 pad_00[0x1c];
    s32 shape;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} HitVolume;

typedef struct Collider {
    void *data;
    VecFx32 max;
    VecFx32 min;
    s32 shape;
} Collider;

typedef struct ActorBody {
    u8 pad_000[0x130];
    Collider collider;
    VecFx32 delta;
    VecFx32 sweptMax;
    VecFx32 sweptMin;
} ActorBody;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x1d];
    u16 flags;
    s8 state;
    u8 pad_53;
    s32 hurtTimer;
} FieldObject;

typedef int (*TouchFunc)(Collider *collider, HitVolume *volume, void *context, int flags);
typedef int (*PushFunc)(Collider *collider, HitVolume *volume, void *context, int flags, VecFx32 *push);

extern ActorBody *ActorRegistry_GetEntityByIndex(int actorId);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern TouchFunc gCollisionTestPairDispatch[][6];
extern PushFunc gCollisionSweepPairDispatch[][6];

int FieldObject_TryCollideWithVolume(FieldObject *object, HitVolume *volume, void *context)
{
    ActorBody *body;
    VecFx32 relative;
    VecFx32 push;
    int result;

    if (object->flags & 8) {
        return 0;
    }
    if (object->flags & 0x800) {
        return 0;
    }
    body = ActorRegistry_GetEntityByIndex(object->actorId);
    if (object->hurtTimer != 0) {
        return 0;
    }
    if (object->state == 0) {
        if (body->sweptMax.x >= volume->min.x && body->sweptMin.x <= volume->max.x &&
            body->sweptMax.z >= volume->min.z && body->sweptMin.z <= volume->max.z &&
            body->sweptMax.y >= volume->min.y && body->sweptMin.y <= volume->max.y) {
            if (volume->velocity.x == 0 && volume->velocity.y == 0 && volume->velocity.z == 0) {
                if (body->delta.x == 0 && body->delta.y == 0 && body->delta.z == 0) {
                    result = 2;
                } else {
                    push = body->delta;
                    result = 1;
                }
            } else {
                VEC_Subtract(&body->delta, &volume->velocity, &relative);
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
                return gCollisionTestPairDispatch[body->collider.shape][volume->shape](&body->collider, volume, context, 0xe);
            }
            return gCollisionSweepPairDispatch[body->collider.shape][volume->shape](&body->collider, volume, context, 0xc, &push);
        }
        return 0;
    }
    return 0;
}
