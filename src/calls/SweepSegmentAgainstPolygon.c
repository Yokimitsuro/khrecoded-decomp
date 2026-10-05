#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct CollisionEdge {
    VecFx32 vertex;
    VecFx32 direction;
    VecFx32 normal;
    u8 pad_24[0xc];
} CollisionEdge;

typedef struct CollisionPolygon {
    CollisionEdge edges[4];
    u8 edgeCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

typedef struct SweepResult {
    s64 enterTime;
    s64 exitTime;
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

extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern BOOL func_0203c26c(CollisionShape *segmentShape, CollisionShape *polygonShape, void *contact, u32 flags);
extern void CopyInitializedRecord13(SweepResult *out);
extern void SubtractVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL DotProductForward(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern void AddVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL SweepAlongProjectedAxis(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern void func_02048b44(VecFx32 *out, const VecFx32 *vec, fx32 scale);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_0204a9f8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FlipVectorIfDotNegative(VecFx32 *a, const VecFx32 *b);
extern void AverageVecs(VecFx32 *out, int count, ...);

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    AddVecFx32Out(&sum, a, b);
    return sum;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    SubtractVecFx32Out(&diff, a, b);
    return diff;
}

static inline VecFx32 AverageOfTwo(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 average;
    AverageVecs(&average, 2, a, b);
    return average;
}

static inline VecFx32 ScaleVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 scaled;
    func_02048b44(&scaled, vec, scale);
    return scaled;
}

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    CopyInitializedRecord13(&result);
    return result;
}

BOOL SweepSegmentAgainstPolygon(CollisionShape *segmentShape, CollisionShape *polygonShape, void *contact, u32 flags, const VecFx32 *velocity)
{
    CollisionSegment *segment = segmentShape->data;
    CollisionPolygon *polygon = polygonShape->data;
    CollisionShape movedShape;
    CollisionSegment moved;
    VecFx32 direction;
    VecFx32 center;
    VecFx32 halfAxis;
    SweepResult result;
    VecFx32 axis;
    VecFx32 edgeNormal;
    VecFx32 offset;
    VecFx32 facing;
    fx32 length;
    fx32 extent;
    u8 edgeCount;
    u8 i;

    if (!(flags & 4)) {
        moved = *segment;
        moved.end = VecAdd(&moved.end, velocity);
        movedShape.data = &moved;
        return func_0203c26c(&movedShape, polygonShape, contact, flags & 1);
    }

    direction = segment->direction;
    length = segment->length;
    if (length == 0) {
        return FALSE;
    }
    center = AverageOfTwo(&segment->start, &segment->end);
    halfAxis = ScaleVec(&direction, length / 2);
    result = MakeSweepResult();
    offset = VecSub(&center, &polygon->edges[0].vertex);
    extent = AbsDotProduct(&halfAxis, &polygon->normal);
    axis = polygon->normal;
    if (!DotProductForward(extent, &offset, &axis, 0, velocity, &result, NULL)) {
        return FALSE;
    }
    edgeCount = polygon->edgeCount;
    facing = direction;
    FlipVectorIfDotNegative(&facing, &polygon->normal);
    for (i = 0; i < edgeCount; i++) {
        if (!func_0204a9f8(&polygon->edges[i].direction, &facing, &edgeNormal)) {
            VEC_Normalize(&edgeNormal, &axis);
            SubtractVecFx32Out(&offset, &center, &polygon->edges[i].vertex);
            if (!SweepAlongProjectedAxis(0, &offset, &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
    }
    return ResolveSweepContact(&result, contact, flags, velocity);
}
