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
    Sphere *data;
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
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x14];
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct Surface {
    u8 pad_00[0x40];
    s32 kind;
} Surface;

typedef struct ActorBody {
    u8 pad_000[0x10c];
    Surface surface;
} ActorBody;

typedef struct {
    u8 pad_00[0x6c];
    s32 kind;
} HitObject;

typedef struct {
    u8 pad_00[0x14];
    s16 normalX;
    s16 normalY;
    s16 normalZ;
} HitPlane;

typedef struct {
    u8 pad_00[8];
    HitPlane *plane;
    u8 pad_0c[4];
    HitObject *object;
    fx32 push;
    VecFx32 normal;
    s32 side;
    u8 pad_28[8];
    HitPlane planeStorage;
} CollisionHit;

typedef struct MoveActor MoveActor;

typedef struct {
    MoveActor *actor;
    s32 blocked;
    s32 grounded;
    u8 pad_0c[0x24];
} SweepContext;

struct MoveActor {
    u8 pad_000[0x10];
    ActorBody body;
    u8 pad_160[0x288 - 0x160];
    u16 stateLow : 2;
    u16 moveKind : 2;
    u16 stateMid : 3;
    u16 blocked : 1;
    u16 stateHigh : 8;
    u8 pad_28a[2];
    u16 moveFlags;
    u8 pad_28e[0x2ee - 0x28e];
    u16 onSlope : 1;
    u16 slopeHigh : 15;
};

extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern fx32 Surface_GetKindValue(Surface *surface);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern CollisionShape func_0203ad28(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern CollisionHit *SweepWorldCollision(CollisionQuery *query);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void FilterPlayerAttackTarget(void);

static inline int GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

CollisionHit *SweepActorStep(MoveActor *actor, const VecFx32 *from, const VecFx32 *delta, VecFx32 *out)
{
    ActorBody *body = &actor->body;
    fx32 radius = 0;
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    SweptShape shape;
    CollisionQuery query;
    VecFx32 center;
    VecFx32 move;
    Sphere sphere;
    SweepContext context;
    QueryFilter filter;
    QueryCallback callback;
    CollisionHit *hit;

    if (GetSessionMode() == 7) {
        return NULL;
    }
    filter.mask = 0x17;
    if (body->surface.kind != -1) {
        radius = Surface_GetKindValue(&body->surface);
    }
    center = *from;
    center.y += radius + 0xcd;
    move = *delta;
    shape.shape = func_0203ad28(&sphere, &center, radius);
    shape.delta = move;
    OffsetBoxByDelta(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    CollisionQuery_Init(&query, actor->moveKind == 1 ? 0x70 : 0, &actor->body, 10, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    context.blocked = 0;
    MI_CpuFill8(&context, 0, sizeof(SweepContext));
    context.actor = actor;
    callback.func = FilterPlayerAttackTarget;
    callback.arg = &context;
    sweep.callback = callback;
    hit = SweepWorldCollision(&sweep);
    if (hit != NULL) {
        if (hit->plane == NULL) {
            hit->plane = &hit->planeStorage;
            if ((u32)(hit->object->kind - 1) <= 1) {
                actor->moveFlags |= 0x8000;
                actor->blocked = 1;
                return NULL;
            }
            hit->plane->normalX = hit->normal.x;
            hit->plane->normalY = hit->normal.y;
            hit->plane->normalZ = hit->normal.z;
        }
        *out = shapeCopy.shape.data->center;
        if (hit->side < 0) {
            VEC_MultAdd(FX_Mul(hit->push, 0x29), &hit->normal, out, out);
            if (GetSessionMode() == 10 || GetSessionMode() == 6) {
                actor->onSlope = context.grounded != 0;
            }
        }
    } else if (context.blocked) {
        actor->moveFlags |= 0x8000;
        actor->blocked = 1;
        VEC_MultAdd(0xfae, delta, from, out);
    }
    return hit;
}
