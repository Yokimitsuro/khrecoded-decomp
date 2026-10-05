#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    u8 pad_000[0x194];
    u8 dead;
} HitOwner;

typedef struct {
    u8 pad_00[0x14];
    HitOwner *owner;
} HitObject;

typedef struct {
    HitObject *object;
    int kind;
    int pad_08;
} ContactHit;

typedef struct {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
    u8 pad_181[0x20];
    u8 locked;
    u8 pad_1a2[2];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u8 pad_000[0x230];
    void *model;
} Enemy;

extern VecFx32 *func_ov052_020ceb74(Enemy *enemy);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(CollisionQuery *query);
extern void func_ov021_020a94d0(void);
extern void func_ov058_020d50cc(Enemy *enemy);

void CheckEnemyContactAbove(Enemy *enemy)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape swept;
    CollisionQuery query;
    CylinderStorage cylinder;
    VecFx32 start;
    VecFx32 end;
    VecFx32 delta;
    VecFx32 axis;
    VecFx32 diff;
    CollisionShape shapeResult;
    QueryCallback callback;
    BOOL landed = FALSE;
    int count;
    int i;

    end = *func_ov052_020ceb74(enemy);
    start = end;
    end.y += 0x19a;
    delta.x = 0;
    delta.y = 0x2000;
    delta.z = 0;
    VEC_Subtract(&end, &start, &diff);
    axis = diff;
    shapeResult = InitCylinderShape(&cylinder, &start, &end, &axis, func_01ffaff4(&axis, &axis), 0x5cd);
    swept.shape = shapeResult;
    swept.delta = delta;
    OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
    sweptCopy = swept;
    CollisionQuery_Init(&query, 0, enemy->model, 8, 1, 1, &sweptCopy, &workspace, NULL);
    sweep = query;
    callback.func = func_ov021_020a94d0;
    callback.arg = NULL;
    sweep.callback = callback;
    if (SweepWorldCollision(&sweep) != NULL && (count = workspace.count) > 0) {
        for (i = 0; i < count; i++) {
            ContactHit *contact = &workspace.hits[i];
            if (contact->kind == 4 && contact->object->owner->dead == 0) {
                landed = TRUE;
                break;
            }
        }
    }
    if (landed) {
        func_ov058_020d50cc(enemy);
    }
}
