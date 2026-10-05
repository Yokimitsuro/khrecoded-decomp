#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct BoxStorage {
    u8 data[0x40];
} BoxStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct CollisionQuery {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    QueryCallback contact;
} CollisionQuery;

typedef struct SweepHit {
    u8 pad_00[0x4];
    void *owner;
    u8 pad_08[0x2c - 0x8];
    VecFx32 normal;
} SweepHit;

typedef struct FieldActor {
    u8 pad_00[0xa8];
    VecFx32 position;
    u8 pad_b4[0x10c - 0xb4];
    u8 collision[0x28];
    s32 bounds[6];
    s32 kind;
    VecFx32 velocity;
    s32 sweptBounds[6];
} FieldActor;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x70 - 0x44];
    u16 drawFlags;
    u8 pad_72[0x84 - 0x72];
    VecFx32 collisionPosition;
    u8 pad_90[0xc0 - 0x90];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    VecFx32 velocity;
    u8 pad_d8[0xe8 - 0xd8];
    s16 hitIndex;
    s16 hitSlot;
} FieldObject;

extern const VecFx32 data_0205344c;
extern const VecFx32 data_ov016_020a6e3c;
extern const MtxFx33 data_02053458;
extern FieldActor *ActorRegistry_GetEntityByIndex(int actorId);
extern BOOL AreVecsWithinRange128(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetCarrierVelocity(FieldObject *object);
extern void func_ov016_020a34e8(VecFx32 *velocity);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void InitBoxShape(CollisionShape *shape, void *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void OffsetBoxByDelta(s32 *src, s32 *dst, VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern SweepHit *SweepWorldCollision(CollisionQuery *query);
extern void func_02034d78(VecFx32 *vec, QueryWorkspace *set);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void SetCollisionObjectPosition(void *object, const VecFx32 *position);
extern void func_ov016_020a2578(FieldObject *object);
extern void IsFieldStateAvailable(void);
extern void OnFieldObjectBumped(void);

void MoveFieldObjectWithCollision(FieldObject *object, BOOL keepVelocity)
{
    QueryWorkspace workspace;
    CollisionQuery query;
    s32 swept[6];
    VecFx32 sweepDelta;
    CollisionShape shape;
    VecFx32 carrier;
    VecFx32 move;
    VecFx32 velocity;
    BoxStorage box;
    VecFx32 center;
    VecFx32 extent;
    VecFx32 normal;
    VecFx32 flatVelocity;
    VecFx32 flatNormal;
    VecFx32 zero;
    VecFx32 initial;
    FieldActor *actor = ActorRegistry_GetEntityByIndex(object->actorId);
    SweepHit *hit;
    BOOL blocked;

    zero = data_0205344c;
    initial = data_0205344c;
    move = initial;
    if (AreVecsWithinRange128(&object->velocity, &data_0205344c) && (object->flags & 0x400)) {
        object->flags &= ~0x400;
        object->velocity = zero;
        object->flags &= ~2;
    }
    carrier = GetCarrierVelocity(object);
    if (!(object->flags & 0x800) || object->velocity.x != 0 || object->velocity.y != 0 || object->velocity.z != 0) {
        object->hitIndex = -1;
        object->hitSlot = -1;
        if (!keepVelocity) {
            func_ov016_020a34e8(&object->velocity);
            object->velocity.y = -0x333;
        }
        velocity = object->velocity;
        VEC_Add(&velocity, &carrier, &velocity);
        center = object->position;
        center.y += 0xc00;
        extent = data_ov016_020a6e3c;
        InitBoxShape(&shape, &box, &center, &extent, &data_02053458);
        sweepDelta = velocity;
        OffsetBoxByDelta(shape.bounds, swept, &sweepDelta);
        blocked = FALSE;
        CollisionQuery_Init(&query, 0, actor, 0xf, 0, 1, &shape, &workspace, NULL);
        query.contact.arg = object;
        query.contact.func = OnFieldObjectBumped;
        query.callback.arg = NULL;
        query.callback.func = IsFieldStateAvailable;
        hit = SweepWorldCollision(&query);
        if (hit != NULL) {
            flatVelocity = velocity;
            normal = hit->normal;
            func_02034d78(&normal, &workspace);
            flatNormal = normal;
            flatNormal.y = 0;
            flatVelocity.y = 0;
            if (VEC_DotProduct(&flatVelocity, &flatNormal) >= 0) {
                move = normal;
                if ((normal.y < 0x80 && normal.y > -0x80) || object->hitIndex != -1) {
                    object->velocity.y = 0;
                }
            } else {
                blocked = TRUE;
            }
            if (blocked) {
                VecFx32 stop = data_0205344c;

                move = stop;
                object->velocity = stop;
            }
        } else {
            move = velocity;
        }
        object->drawFlags |= 0x20;
        if ((hit != NULL && hit->owner != NULL) || object->hitIndex != -1) {
            object->flags |= 0x800;
        } else {
            object->flags &= ~0x800;
        }
    } else {
        move = zero;
    }
    actor->velocity = move;
    OffsetBoxByDelta(actor->bounds, actor->sweptBounds, &actor->velocity);
    VEC_Add(&object->position, &move, &object->position);
    SetCollisionObjectPosition(actor->collision, &object->collisionPosition);
    actor->position = object->position;
    func_ov016_020a2578(object);
}
