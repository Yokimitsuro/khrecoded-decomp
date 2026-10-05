#include "nitro/types.h"
#include "nitro/fx_types.h"

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
extern void NormalizeVectorInto(VecFx32 *dest, const VecFx32 *src);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 GetProjectedInterval(CollisionPolygon *shape, const VecFx32 *axis, fx32 *center);
extern BOOL UpdateSignedPenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, HitResult *result);
extern BOOL func_0204a9f8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void WritePenetrationContact(const HitResult *result, void *contact, u32 flags);

static inline HitResult MakeMaxDistanceHit(void)
{
    HitResult result;
    InitMaxDistanceHit(&result);
    return result;
}

static inline VecFx32 NormalizedVec(const VecFx32 *vec)
{
    VecFx32 result;
    NormalizeVectorInto(&result, vec);
    return result;
}

BOOL TestPolygonAgainstPolygon(CollisionPolygon **refA, CollisionPolygon **refB, void *contact, u32 flags)
{
    HitResult hit = MakeMaxDistanceHit();
    CollisionPolygon *polygons[2];
    CollisionPolygon *polyA;
    CollisionPolygon *polyB;
    u8 countA;
    u8 countB;
    u8 side;
    u8 edgeA;
    u8 edgeB;

    polygons[0] = *refA;
    polygons[1] = *refB;
    for (side = 0; side < 2; side++) {
        CollisionPolygon *polygon = polygons[side];
        fx32 center;
        fx32 extent = GetProjectedInterval(polygons[(u8)(side ^ 1)], &polygon->normal, &center);
        fx32 distance = center - VEC_DotProduct(&polygon->vertices[0].position, &polygon->normal);
        if (side != 1) {
            distance = -distance;
        }
        if (!UpdateSignedPenetrationDepth(extent, distance, &polygon->normal, 0, &hit)) {
            return FALSE;
        }
    }
    polyA = polygons[0];
    polyB = polygons[1];
    countA = polyA->vertexCount;
    countB = polyB->vertexCount;
    for (edgeA = 0; edgeA < countA; edgeA++) {
        for (edgeB = 0; edgeB < countB; edgeB++) {
            VecFx32 cross;
            if (!func_0204a9f8(&polyA->vertices[edgeA].edgeDir, &polyB->vertices[edgeB].edgeDir, &cross)) {
                VecFx32 axis = NormalizedVec(&cross);
                fx32 centerA;
                fx32 centerB;
                fx32 extentA = GetProjectedInterval(polyA, &axis, &centerA);
                fx32 extentB = GetProjectedInterval(polyB, &axis, &centerB);
                if (!UpdateSignedPenetrationDepth(extentA + extentB, centerA - centerB, &axis, 0, &hit)) {
                    return FALSE;
                }
            }
        }
    }
    WritePenetrationContact(&hit, contact, flags);
    return TRUE;
}
