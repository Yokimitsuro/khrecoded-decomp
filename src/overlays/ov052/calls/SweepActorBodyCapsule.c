#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
    VecFx32 axis;
    fx32 length;
    fx32 radius;
} CollisionCapsule;

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct {
    u32 data[0x18];
} CollisionQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    void *first;
    void *second;
    void *third;
} IgnorePair;

typedef struct {
    IgnorePair *entries;
    int count;
} IgnoreList;

typedef struct {
    u8 pad_00[4];
    fx32 minY;
    u8 pad_08[8];
    fx32 maxY;
} BodyBounds;

typedef struct {
    u8 pad_000[0x130];
    BodyBounds *bounds;
} BodyModel;

typedef struct {
    u8 pad_000[0x230];
    BodyModel *model;
} BodyActor;

extern VecFx32 *func_ov052_020ceb74(BodyActor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCapsuleShape(CollisionShape *shape, CollisionCapsule *capsule, const VecFx32 *start, const VecFx32 *end,
                                      const VecFx32 *axis, fx32 length, fx32 radius);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *owner, u8 kind, u8 unk3C, u8 unk3D, CollisionShape *shape, QueryWorkspace *workspace, IgnoreList *ignore);
extern void *SweepWorldCollision(CollisionQuery *query);

void SweepActorBodyCapsule(BodyActor *actor)
{
    CollisionQuery query;
    QueryWorkspace workspace;
    CollisionQuery setup;
    CollisionShape shapeCopy;
    CollisionCapsule capsule;
    IgnorePair ignoreEntries;
    VecFx32 base;
    VecFx32 top;
    VecFx32 bottom;
    CollisionShape shape;
    VecFx32 diff;
    VecFx32 axis;
    IgnoreList ignore;
    IgnoreList ignoreSource;
    VecFx32 *position = func_ov052_020ceb74(actor);
    BodyBounds *bounds = actor->model->bounds;
    fx32 height = bounds->maxY - bounds->minY;

    base.x = position->x;
    base.y = position->y + 0x900;
    base.z = position->z;
    top = base;
    bottom = base;
    top.y += height - 0x900;
    top.y = (top.y >= bottom.y + 0x80) ? top.y : bottom.y + 0x80;
    VEC_Subtract(&bottom, &top, &diff);
    axis = diff;
    InitCapsuleShape(&shape, &capsule, &top, &bottom, &axis, func_01ffaff4(&axis, &axis), 0x900);
    shapeCopy = shape;
    ignoreEntries.first = &actor->model;
    ignoreEntries.second = NULL;
    ignoreSource.entries = &ignoreEntries;
    ignoreSource.count = 2;
    ignore = ignoreSource;
    CollisionQuery_Init(&setup, 0, actor->model, 8, 0, 0, &shapeCopy, &workspace, &ignore);
    query = setup;
    SweepWorldCollision(&query);
}
