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
    u32 words[0x18];
} CollisionQuery;

typedef struct Surface {
    u8 pad_00[0x40];
    s32 kind;
} Surface;

typedef struct ActorBody {
    u8 pad_000[0x10c];
    Surface surface;
} ActorBody;

typedef struct ProbeActor {
    u8 pad_000[0x10];
    ActorBody body;
    u8 pad_160[0x2b4 - 0x160];
    fx32 stepHeight;
    u8 pad_2b8[0x2c4 - 0x2b8];
    fx32 headHeight;
} ProbeActor;

extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern fx32 Surface_GetKindValue(Surface *surface);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern CollisionShape func_0203ad28(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern BOOL SweepWorldCollision(CollisionQuery *query);

BOOL ProbeCeilingAboveActor(ProbeActor *actor, const VecFx32 *from, VecFx32 *out)
{
    ActorBody *body = &actor->body;
    fx32 radius = 0;
    fx32 height;
    int mode;
    BOOL hit;
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    SweptShape shape;
    CollisionQuery query;
    VecFx32 center;
    VecFx32 delta;
    Sphere sphere;
    QueryFilter filter;

    if (func_ov001_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    if (mode == 7) {
        return FALSE;
    }
    if (from == NULL) {
        return FALSE;
    }
    if (from->y < actor->headHeight) {
        return FALSE;
    }
    filter.mask = 0x17;
    if (body->surface.kind != -1) {
        radius = Surface_GetKindValue(&body->surface);
    }
    height = actor->stepHeight + radius;
    center.x = from->x;
    center.y = actor->headHeight + height;
    center.z = from->z;
    delta.x = 0;
    delta.y = 0xa000;
    delta.z = 0;
    shape.shape = func_0203ad28(&sphere, &center, FX_Mul(0xccd, radius));
    shape.delta = delta;
    OffsetBoxByDelta(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    CollisionQuery_Init(&query, 0x7f, &actor->body, 0xc, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    hit = SweepWorldCollision(&sweep);
    if (hit && shapeCopy.shape.data->center.y <= from->y + height) {
        out->y = shapeCopy.shape.data->center.y - height;
        return hit;
    }
    return FALSE;
}
