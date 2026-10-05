#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x28];
} ShapeStorage;

typedef struct {
    u32 data[0x18];
} CollisionQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u8 pad_00[0x80];
    u8 meshIndices[4];
} HitSurface;

typedef struct {
    u8 pad_00[8];
    HitSurface *surface;
} CollisionHit;

typedef struct {
    u8 pad_000[0x230];
    void *model;
    u8 pad_234[0xa54 - 0x234];
    VecFx32 probeOrigin;
} ProbeActor;

extern s16 data_02053580[];
extern u16 GetLinkedAngleOffset(ProbeActor *actor);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203ade0(ShapeStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, CollisionShape *shape, QueryWorkspace *workspace, void *filter);
extern CollisionHit *SweepWorldCollision(CollisionQuery *query);
extern void *GetWorldMeshNamedEntry(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);

BOOL IsForwardPathBlocked(ProbeActor *actor, BOOL raised)
{
    VecFx32 *origin = &actor->probeOrigin;
    CollisionQuery query;
    QueryWorkspace workspace;
    CollisionQuery setup;
    ShapeStorage storage;
    CollisionShape shapeCopy;
    VecFx32 start;
    VecFx32 end;
    VecFx32 forward;
    CollisionShape shape;
    VecFx32 diff;
    VecFx32 axis;
    BOOL result;
    CollisionHit *hit;
    int i;
    void *mesh;
    int index;

    result = FALSE;
    start = *origin;
    if (raised) {
        start.y = origin->y + 0x1b33;
    }
    forward.z = 0;
    forward.y = 0;
    forward.x = 0;
    index = GetLinkedAngleOffset(actor) >> 4;
    forward.x = -data_02053580[index];
    forward.z = -data_02053580[(0x400 - index) & 0xfff];
    VEC_MultAdd(0x800, &forward, &start, &end);
    VEC_Subtract(&end, &start, &diff);
    axis = diff;
    shape = func_0203ade0(&storage, &start, &end, &axis, func_01ffaff4(&axis, &axis));
    shapeCopy = shape;
    CollisionQuery_Init(&setup, 0, actor->model, 2, 1, 0, &shapeCopy, &workspace, NULL);
    query = setup;
    hit = SweepWorldCollision(&query);
    if (hit != NULL) {
        for (i = 0; i < 4; i++) {
            mesh = GetWorldMeshNamedEntry(hit->surface->meshIndices[i]);
            if (mesh != NULL && func_ov001_020681e8(mesh, 7)) {
                result = TRUE;
                break;
            }
        }
    } else {
        result = TRUE;
    }
    return result;
}
