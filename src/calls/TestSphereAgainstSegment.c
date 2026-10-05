#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
} SphereShapeRef;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
} SegmentShapeRef;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern BOOL TestSphereAgainstPoint(const VecFx32 *point, const CollisionSphere *sphere, CollisionHit *hit, u32 flags);
extern int PXI_Init_0203f23c(int value);
extern VecFx32 SubtractVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern fx32 DivideShifted27(fx32 numer, fx32 denom);
extern VecFx32 VecFx32ScaledCopy(const VecFx32 *v, fx32 scale);
extern BOOL IsNearOrigin(const VecFx32 *vec);
extern VecFx32 ComputeNormalizedCrossInto(const VecFx32 *v);
extern VecFx32 NormalizeVectorInto(const VecFx32 *src);
extern VecFx32 func_0203f5c0(const CollisionHit *hit, const CollisionSegment *segment);
extern VecFx32 NormalizeVectorAltInto(const VecFx32 *src);
extern fx32 MultiplyShiftRight27(fx32 a, fx32 b);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);

BOOL TestSphereAgainstSegment(SphereShapeRef *sphereRef, SegmentShapeRef *segmentRef, CollisionHit *hit, u32 flags)
{
    CollisionSphere *sphere = sphereRef->sphere;
    CollisionSegment *segment = segmentRef->segment;
    VecFx32 delta = SubtractVecFx32Into(&sphere->center, &segment->start);
    fx32 distance = func_01ffaff4(&delta, &delta);
    VecFx32 direction = segment->direction;
    fx32 length = segment->length;
    fx32 cosine = VEC_DotProduct(&direction, &delta);
    fx32 perpendicular;
    fx32 along;

    if (cosine <= 0) {
        if (flags & 0x10) {
            if (hit != NULL) {
                hit->time = 0;
            }
            return TestSphereAgainstPoint(&segment->start, sphere, hit, !(flags & 1));
        }
        return FALSE;
    }
    perpendicular = FX_Mul(ComputeOneMinusSquareFraction(cosine), distance);
    if (perpendicular > sphere->radius) {
        return FALSE;
    }
    if (hit == NULL) {
        return TRUE;
    }
    hit->kind = 1;
    along = FX_Mul(cosine, distance);
    hit->time = DivideShifted27(along - FX_Mul(cosine, sphere->radius), length);
    if (hit->time < -1) {
        hit->time = -1;
    }
    if (!(flags & 1)) {
        if (along <= length) {
            hit->depth = sphere->radius - perpendicular;
            VEC_Subtract(&delta, &VecFx32ScaledCopy(&direction, cosine), &delta);
            if (IsNearOrigin(&delta)) {
                hit->normal = ComputeNormalizedCrossInto(&direction);
            } else {
                hit->normal = NormalizeVectorInto(&delta);
            }
            return TRUE;
        }
        return TestSphereAgainstPoint(&segment->end, sphere, hit, !(flags & 1));
    } else {
        VecFx32 point = func_0203f5c0(hit, segment);
        VecFx32 offset = SubtractVecFx32Into(&point, &sphere->center);
        hit->normal = NormalizeVectorAltInto(&offset);
        hit->depth = MultiplyShiftRight27(FX_Mul(length, PXI_Init_0203f23c(VEC_DotProduct(&direction, &hit->normal))), 0x8000000 - hit->time);
        return TRUE;
    }
}
