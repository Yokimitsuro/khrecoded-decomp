#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    u8 *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x3d];
    fx32 rotation[6];
    VecFx32 offset;
} Obj;

typedef struct {
    u8 pad_000[0x130];
    CollisionShape shape;
    VecFx32 delta;
    s32 sweptBounds[6];
} Actor;

extern const VecFx32 data_0205344c;
extern ComputeBoundsFunc gCollisionBoundsDispatch[];

extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void MTX_Identity33_(void *mtx);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern void UpdateBoxAxisAlignedFlag(void *data);

static inline void ComputeBounds(CollisionShape *shape)
{
    gCollisionBoundsDispatch[shape->kind](shape, (s32 *)((u8 *)shape + 4));
}

void ResetObjectRotation(Obj *obj)
{
    Actor *actor = ActorRegistry_GetEntityByIndex(obj->actorId);

    obj->rotation[0] = 0;
    obj->rotation[1] = 0;
    obj->rotation[2] = 0x1000;
    obj->rotation[3] = 0;
    obj->rotation[4] = 0x1000;
    obj->rotation[5] = 0;
    obj->offset = data_0205344c;
    MTX_Identity33_(actor->shape.data + 0x18);
    ComputeBounds(&actor->shape);
    OffsetBoxByDelta(actor->shape.bounds, actor->sweptBounds, &actor->delta);
    UpdateBoxAxisAlignedFlag(actor->shape.data);
}


