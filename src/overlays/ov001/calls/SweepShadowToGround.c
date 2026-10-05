#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void *func;
    void *context;
} QueryCallback;

typedef struct {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct {
    u8 pad_00[0x48];
    QueryCallback filter;
    u8 pad_50[0x10];
} CollisionQuery;

typedef struct ShadowBody {
    u8 pad_000[0x10];
    u8 actor[0xa8];
    VecFx32 center;
} ShadowBody;

typedef struct ShadowedActor {
    u8 pad_00[0xc];
    ShadowBody *body;
} ShadowedActor;

extern CollisionShape func_0203ad28(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern BOOL SweepWorldCollision(CollisionQuery *query);
extern BOOL func_ov001_020847ec();

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = value;
    filter.mask = mask;
    return filter;
}

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

void SweepShadowToGround(ShadowedActor *actor, VecFx32 *out)
{
    SweptShape shapeCopy;
    QueryWorkspace workspace;
    CollisionQuery sweep;
    SweptShape shape;
    CollisionQuery query;
    Sphere sphere;
    VecFx32 delta;
    QueryFilter filter;

    delta = MakeVec(0, -0x50000, 0);
    shape.shape = func_0203ad28(&sphere, &actor->body->center, 0x266);
    shape.delta = delta;
    OffsetBoxByDelta(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    filter = MakeFilter(0, 0x15);
    CollisionQuery_Init(&query, 0, actor->body->actor, 0xb, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    sweep.filter = MakeCallback(func_ov001_020847ec, actor);
    SweepWorldCollision(&sweep);
    *out = sphere.center;
    out->y -= 0x266;
}
