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

typedef struct SweepResult {
    u32 enterTimeLo;
    s32 enterTimeHi;
    u32 exitTimeLo;
    s32 exitTimeHi;
    VecFx32 enterAxis;
    fx32 minDepth;
    VecFx32 depthAxis;
    s8 depthSign;
    u8 depthFeature;
    u8 pad_2E[2];
    s8 enterSign;
    u8 touching;
    u8 enterFeature;
    u8 pad_33;
} SweepResult;

extern SweepResult CopyInitializedRecord13(void);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 GetProjectedInterval(CollisionPolygon *shape, const VecFx32 *axis, fx32 *center);
extern BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern BOOL func_0204a9f8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NormalizeVectorOut(VecFx32 *dst, const VecFx32 *src);

static inline VecFx32 NormalizedVec(const VecFx32 *vec)
{
    VecFx32 result;
    NormalizeVectorOut(&result, vec);
    return result;
}

BOOL SweepPolygonAgainstPolygon(CollisionPolygon **refA, CollisionPolygon **refB, void *contact, u32 flags, const VecFx32 *velocity)
{
    SweepResult result = CopyInitializedRecord13();
    CollisionPolygon *polygons[2];
    CollisionPolygon *polyA;
    CollisionPolygon *polyB;
    VecFx32 axis;
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
        axis = polygon->normal;
        if (side != 1) {
            distance = -distance;
        }
        if (!SweepIntervalOnAxis(extent, distance, &axis, 0, velocity, &result, NULL)) {
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
                VecFx32 normal = NormalizedVec(&cross);
                fx32 centerA;
                fx32 centerB;
                fx32 extentA = GetProjectedInterval(polyA, &normal, &centerA);
                fx32 extentB = GetProjectedInterval(polyB, &normal, &centerB);
                axis = normal;
                if (!SweepIntervalOnAxis(extentA + extentB, centerA - centerB, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }
    return ResolveSweepContact(&result, contact, flags, velocity);
}
