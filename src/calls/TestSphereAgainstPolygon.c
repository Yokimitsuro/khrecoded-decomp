#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct PolygonVertex {
    VecFx32 position;
    VecFx32 edgeDir;
    VecFx32 edgeNormal;
    u8 pad_24[0xc];
} PolygonVertex;

typedef struct CollisionPolygon {
    PolygonVertex vertices[4];
    u8 vertexCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

typedef struct HitResult {
    s32 distance;
    s32 data[4];
} HitResult;

extern void InitMaxDistanceHit(HitResult *result);
extern void SubtractVecFx32Into(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b);
extern void NormalizeVectorInto(VecFx32 *dest, const VecFx32 *src);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL IsVecZero(const VecFx32 *vec);
extern BOOL func_0203fbb8(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, HitResult *result);
extern BOOL func_0203fbf8(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, HitResult *result);
extern void GetUnitRejectionFromAxis(VecFx32 *out, const VecFx32 *vec, const VecFx32 *dir);
extern void WritePenetrationContact(const HitResult *result, void *contact, u32 flags);

static inline HitResult MakeMaxDistanceHit(void)
{
    HitResult result;
    InitMaxDistanceHit(&result);
    return result;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    SubtractVecFx32Into(&result, a, b);
    return result;
}

BOOL TestSphereAgainstPolygon(Sphere **sphereRef, CollisionPolygon **polygonRef, void *contact, u32 flags)
{
    Sphere *sphere = *sphereRef;
    CollisionPolygon *polygon = *polygonRef;
    HitResult hit = MakeMaxDistanceHit();
    VecFx32 axis;
    VecFx32 diff = SubtractVec(&sphere->center, &polygon->vertices[0].position);
    u32 count;
    u8 i;

    if (!func_0203fbb8(sphere->radius, &diff, &polygon->normal, 0, &hit)) {
        return FALSE;
    }
    count = polygon->vertexCount;
    for (i = 0; i < count; i++) {
        SubtractVecFx32Into(&diff, &sphere->center, &polygon->vertices[i].position);
        if (VEC_DotProduct(&diff, &polygon->vertices[i].edgeNormal) >= 0) {
            GetUnitRejectionFromAxis(&axis, &diff, &polygon->vertices[i].edgeDir);
            if (!func_0203fbf8(sphere->radius, &diff, &axis, 1, &hit)) {
                return FALSE;
            }
            if (VEC_DotProduct(&diff, &polygon->vertices[i].edgeDir) < 0) {
                NormalizeVectorInto(&axis, &diff);
            } else {
                SubtractVecFx32Into(&diff, &sphere->center, &polygon->vertices[(i + 1) % (int)count].position);
                if (IsVecZero(&diff)) {
                    continue;
                }
                NormalizeVectorInto(&axis, &diff);
                if (VEC_DotProduct(&diff, &polygon->vertices[i].edgeDir) <= 0) {
                    continue;
                }
            }
            if (!func_0203fbf8(sphere->radius, &diff, &axis, 1, &hit)) {
                return FALSE;
            }
        }
    }
    WritePenetrationContact(&hit, contact, flags);
    return TRUE;
}
