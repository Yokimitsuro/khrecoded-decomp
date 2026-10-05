#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweepShape;

typedef struct {
    u32 data[0x18];
} CollisionQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u8 pad_000[0x230];
    void *collisionOwner;
    u8 pad_234[0xa0c - 0x234];
    fx32 riseSpeed;
} HeadroomActor;

extern VecFx32 *func_ov052_020ceb74(HeadroomActor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                       const VecFx32 *direction, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const s32 *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *owner, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, s32 unk44);
extern void *SweepWorldCollision(CollisionQuery *query);

BOOL CheckHeadroomClear(HeadroomActor *actor)
{
    BOOL result = TRUE;
    CollisionQuery query;
    QueryWorkspace workspace;
    SweepShape sweepCopy;
    SweepShape sweep;
    CollisionQuery setup;
    VecFx32 start;
    VecFx32 end;
    VecFx32 delta;
    CollisionCylinder cylinder;
    VecFx32 direction;
    VecFx32 diff;
    CollisionShape shape;

    end = *func_ov052_020ceb74(actor);
    start = end;
    end.y += 0x200;
    delta.x = 0;
    delta.y = actor->riseSpeed + 0x333;
    delta.z = 0;
    VEC_Subtract(&end, &start, &diff);
    direction = diff;
    InitCylinderShape(&shape, &cylinder, &start, &end, &direction, func_01ffaff4(&direction, &direction), 0x900);
    sweep.shape = shape;
    sweep.delta = delta;
    OffsetBoxByDelta(sweep.shape.bounds, &sweep.sweptBounds, &sweep.delta);
    sweepCopy = sweep;
    CollisionQuery_Init(&setup, 0, actor->collisionOwner, 0xf, 1, 1, &sweepCopy, &workspace, 0);
    query = setup;
    if (SweepWorldCollision(&query)) {
        result = FALSE;
    }
    return result;
}
