#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    BOOL (*func)(void *ref, void *query);
    void *arg;
} QueryCallback;

typedef struct {
    u8 pad_00[0x50];
    QueryCallback callback;
    u8 pad_58[8];
} SweepQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
    VecFx32 delta;
    s32 sweptBounds[6];
} SweepShape;

typedef struct {
    u8 data[0x10];
} ShapeExtent;

typedef struct {
    u8 pad_00[0x2c];
    VecFx32 normal;
} SweepHit;

extern void func_0203ad28(SweepShape *shape, ShapeExtent *extent, VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(s32 *src, s32 *dst, VecFx32 *delta);
extern void CollisionQuery_Init(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, s32 unk44);
extern SweepHit *SweepWorldCollision(SweepQuery *query);
extern void func_02034d78(VecFx32 *vec, QueryWorkspace *set);
extern BOOL IsQueryFacingContact(void *ref, void *query);

SweepHit *SweepSphereAgainstWorld(const VecFx32 *position, int mask, fx32 radius, const VecFx32 *move, VecFx32 *outMove)
{
    QueryCallback callback;
    VecFx32 center;
    ShapeExtent extent;
    QueryWorkspace workspace;
    SweepShape shape;
    SweepQuery query;
    SweepShape initShape;
    SweepQuery initQuery;
    SweepHit *hit;

    center = *position;
    center.y += radius;
    func_0203ad28(&initShape, &extent, &center, radius);
    initShape.delta = *move;
    OffsetBoxByDelta(initShape.bounds, initShape.sweptBounds, &initShape.delta);
    shape = initShape;
    CollisionQuery_Init(&initQuery, 0, NULL, mask, 0, 1, &shape, &workspace, 0);
    query = initQuery;
    callback.func = IsQueryFacingContact;
    callback.arg = NULL;
    query.callback = callback;
    hit = SweepWorldCollision(&query);
    if (hit != NULL) {
        *outMove = hit->normal;
        func_02034d78(outMove, &workspace);
        return hit;
    }
    *outMove = *move;
    return hit;
}
