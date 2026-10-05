#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 max;
    VecFx32 min;
} CollisionBox;

typedef struct CollisionBody {
    u8 pad_00[0x4];
    CollisionBox baseBox;
    int kind;
    VecFx32 velocity;
    CollisionBox sweptBox;
} CollisionBody;

typedef struct FieldActor {
    u8 pad_00[0x130];
    CollisionBody body;
} FieldActor;

typedef struct FieldObject {
    u8 pad_00[0x2C];
    int linkId;
    u8 pad_30[0x2];
    u8 actorId;
    u8 pad_33[0xBE - 0x33];
    u8 unk_BE_lo : 4;
    u8 motionState : 4;
    u8 pad_BF;
    u32 flags;
    u8 pad_C4[0x4];
    void *unk_C8;
} FieldObject;

typedef int (*RestingHandler)(CollisionBody *self, CollisionBody *other, void *context, int mask);
typedef int (*MovingHandler)(CollisionBody *self, CollisionBody *other, void *context, int mask, VecFx32 *relativeVelocity);

extern RestingHandler gCollisionTestPairDispatch[][6];
extern MovingHandler gCollisionSweepPairDispatch[][6];
extern BOOL IsNodeFlagBitClear(FieldObject *object);
extern FieldActor *ActorRegistry_GetEntityByIndex(int actorId);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int DispatchActorCollision(FieldObject *object, CollisionBody *other, void *context)
{
    if (object->flags & 0x1012) {
        return 0;
    }
    if (object->unk_C8 != NULL) {
        return 0;
    }
    if (!IsNodeFlagBitClear(object)) {
        return 0;
    }
    if (object->motionState == 0 && object->linkId != -1) {
        FieldActor *actor = ActorRegistry_GetEntityByIndex(object->actorId);
        VecFx32 diff;
        VecFx32 relativeVelocity;
        int contact;
        if (actor->body.sweptBox.max.x >= other->sweptBox.min.x && actor->body.sweptBox.min.x <= other->sweptBox.max.x &&
            actor->body.sweptBox.max.z >= other->sweptBox.min.z && actor->body.sweptBox.min.z <= other->sweptBox.max.z &&
            actor->body.sweptBox.max.y >= other->sweptBox.min.y && actor->body.sweptBox.min.y <= other->sweptBox.max.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                if (actor->body.velocity.x == 0 && actor->body.velocity.y == 0 && actor->body.velocity.z == 0) {
                    contact = 2;
                } else {
                    relativeVelocity = actor->body.velocity;
                    contact = 1;
                }
            } else {
                VEC_Subtract(&actor->body.velocity, &other->velocity, &diff);
                relativeVelocity = diff;
                if (relativeVelocity.x == 0 && relativeVelocity.y == 0 && relativeVelocity.z == 0) {
                    contact = 2;
                } else {
                    contact = 1;
                }
            }
        } else {
            contact = 0;
        }
        if (contact != 0) {
            if (contact == 2) {
                return gCollisionTestPairDispatch[actor->body.kind][other->kind](&actor->body, other, context, 0xE);
            }
            return gCollisionSweepPairDispatch[actor->body.kind][other->kind](&actor->body, other, context, 0xC, &relativeVelocity);
        }
        return 0;
    }
    return 0;
}
