#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CylinderData {
    u8 pad_00[4];
    fx32 y;
    u8 pad_08[0x1c];
    fx32 height;
    fx32 radius;
} CylinderData;

typedef struct CollisionShape {
    CylinderData *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweepShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBox;
} SweepShape;

typedef struct BoxStorage {
    u8 data[0x40];
} BoxStorage;

typedef struct QueryCallback {
    void *func;
    void *context;
} QueryCallback;

typedef struct CollisionQuery {
    u32 words[9];
    SweepShape *shape;
    u32 pad_28;
    s32 limit;
    u32 pad_30[8];
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct ContactHit {
    void *object;
    int kind;
    int pad_08;
} ContactHit;

typedef struct QueryWorkspace {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
    u8 hitIndex;
    u8 pad_182[0x1f];
    u8 hitType;
    u8 pad_1a2[2];
} QueryWorkspace;

typedef struct HitRecord {
    u8 pad_00[0x2c];
    VecFx32 position;
} HitRecord;

typedef struct Collider {
    u8 pad_00[0xe];
    u16 id;
    void *actor;
    u8 pad_14[0x10];
    SweepShape *shape;
    u8 pad_28[0x1c];
    s32 filter;
} Collider;

extern const VecFx32 data_0205344c;
extern void Request_IsIdle(void);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, s32 filter);
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void InitBoxShape(CollisionShape *shape, void *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern HitRecord *CollWorld_FindHit(void *world, CollisionQuery *query);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void *GetSubStruct1C(void);
extern BOOL func_0204a9f8(const VecFx32 *normal, void *ref, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void NegateVecFx32(VecFx32 *vec);

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

void Collider_ComputeBoxPushOut(void *world, int unused1, Collider *collider, int unused3, const VecFx32 *pos, VecFx32 *out)
{
    QueryWorkspace workspace;
    CollisionQuery sweep;
    CollisionQuery query;
    SweepShape shape;
    BoxStorage storage;
    VecFx32 center;
    VecFx32 extent;
    MtxFx33 rotation;
    VecFx32 centerValue;
    VecFx32 extentValue;
    MtxFx33 rotationValue;
    VecFx32 zero;
    CylinderData *cylinder = collider->shape->shape.data;
    HitRecord *hit;
    fx32 half;

    if (cylinder->y < -cylinder->radius) {
        return;
    }
    half = cylinder->radius + cylinder->height / 2;
    CollisionQuery_Init(&query, collider->id, collider->actor, 0xf, 0, 1, collider->shape, &workspace, collider->filter);
    sweep = query;
    MTX_Identity33_(&rotationValue);
    rotation = rotationValue;
    extentValue.x = 0x733;
    extentValue.y = half;
    extentValue.z = 0x4000;
    extent = extentValue;
    centerValue.x = pos->x;
    centerValue.y = pos->y + half;
    centerValue.z = pos->z;
    center = centerValue;
    InitBoxShape(&shape.shape, &storage, &center, &extent, &rotation);
    zero = data_0205344c;
    shape.delta = data_0205344c;
    OffsetBoxByDelta(&shape.shape.bounds, &shape.sweptBox, &shape.delta);
    *sweep.shape = shape;
    sweep.shape->sweptBox.minZ = pos->z + collider->shape->shape.data->radius;
    sweep.shape->sweptBox.maxZ = pos->z - collider->shape->shape.data->radius;
    sweep.shape->sweptBox.minY = pos->y + half * 2;
    sweep.shape->sweptBox.maxY = pos->y + 0x10;
    sweep.shape->shape.bounds = sweep.shape->sweptBox;
    sweep.limit = 0x7fffffff;
    sweep.callback = MakeCallback(Request_IsIdle, NULL);
    hit = CollWorld_FindHit(world, &sweep);
    if (hit != NULL) {
        if (workspace.hitType == 0) {
            *out = hit->position;
            out->z = 0;
            if (out->x != 0 && out->y != 0) {
                out->y = 0;
            }
        } else if (workspace.hitType <= 2) {
            VecFx32 *normal = &workspace.normals[workspace.hitIndex];
            fx32 dot = VEC_DotProduct(&hit->position, normal);
            VecFx32 result;
            VecFx32 scaled;
            VecFx32 projected;

            scaled = *normal;
            ScaleVecFx32InPlace(&scaled, dot);
            projected = scaled;
            VEC_Subtract(&hit->position, &projected, &result);
            *out = result;
            out->z = 0;
            if (out->x == 0 && out->y == 0 && out->z == 0) {
                if (func_0204a9f8(&workspace.normals[workspace.hitIndex], GetSubStruct1C(), out)) {
                    out->x = 0;
                    out->y = FX32_ONE;
                    out->z = 0;
                } else {
                    VEC_Normalize(out, out);
                }
                ScaleVecFx32InPlace(out, 0x333);
            }
            if (out->x != 0 && out->y != 0) {
                out->y = 0;
            } else if (out->y < 0) {
                NegateVecFx32(out);
            } else if (out->y == 0) {
                int posSign = pos->x >= 0 ? 1 : -1;
                int outSign = out->x >= 0 ? 1 : -1;
                if (outSign == posSign) {
                    out->x = -out->x;
                    if ((out->x < 0 ? -out->x : out->x) > (pos->x < 0 ? -pos->x : pos->x)) {
                        out->x = (pos->x >= 0 ? pos->x : -pos->x) * (out->x >= 0 ? 1 : -1);
                    }
                }
            }
        } else {
            *out = zero;
        }
    }
}
