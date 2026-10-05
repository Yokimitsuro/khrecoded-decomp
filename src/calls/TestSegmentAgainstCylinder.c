#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern fx32 ComputeDirectionalExtent(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);
extern VecFx32 SubtractVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern BOOL IsNearOrigin(const VecFx32 *vec);
extern VecFx32 NormalizeVectorInto(const VecFx32 *src);
extern VecFx32 AddVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Into(const VecFx32 *src);
extern PenetrationResult InitMaxDistanceHit(void);
extern BOOL func_0203fbb8(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern VecFx32 GetSegmentHalfDelta(const CollisionCylinder *cylinder);
extern VecFx32 ComputeCrossProduct(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 ComputeVectorRejection(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 GetSegmentHalfDirection(const CollisionCylinder *cylinder);
extern void func_02041048(VecFx32 *out, fx32 x, fx32 y, fx32 z);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern void GetPerpendicularVector(VecFx32 *out, const VecFx32 *v);
extern VecFx32 AverageVecs(s32 count, ...);

BOOL TestSegmentAgainstCylinder(CylinderShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    CollisionCylinder *segment = segmentRef->cylinder;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    BOOL isCapsule = cylinderRef->kind == 3;
    PenetrationResult result = InitMaxDistanceHit();
    VecFx32 segmentCenter = AverageVecs(2, &segment->start, &segment->end);
    VecFx32 cylinderCenter = AverageVecs(2, &cylinder->start, &cylinder->end);
    VecFx32 delta = SubtractVecFx32Into(&segmentCenter, &cylinderCenter);
    VecFx32 normal;
    VecFx32 segmentHalf = GetSegmentHalfDelta(segment);
    VecFx32 cylinderHalf = GetSegmentHalfDirection(cylinder);
    VecFx32 cross = ComputeCrossProduct(&segmentHalf, &cylinderHalf);
    BOOL parallel = IsNearOrigin(&cross);
    u8 i;

    if (parallel) {
        normal = ComputeVectorRejection(&delta, &NormalizeVectorInto(&segmentHalf));
        if (IsNearOrigin(&normal)) {
            GetPerpendicularVector(&normal, &segmentHalf);
        }
    } else {
        normal = cross;
    }
    func_01ffaff4(&normal, &normal);
    if (!func_0203fbb8(cylinder->radius, &delta, &normal, 0, &result)) {
        return FALSE;
    }
    {
        VecFx32 segmentAxis = segment->direction;
        VecFx32 cylinderAxis = cylinder->direction;
        fx32 length = cylinder->length;
        u8 j;

        if (!parallel) {
            VecFx32 *axes[2];
            VecFx32 *halves[2];
            axes[0] = &segmentAxis;
            axes[1] = &cylinderAxis;
            halves[0] = &segmentHalf;
            halves[1] = &cylinderHalf;
            for (i = 0; i < 2; i++) {
                VecFx32 *axis = axes[i];
                VecFx32 *otherHalf = halves[(u8)(i ^ 1)];
                fx32 extent;
                VecFx32 toNear = ComputeVectorRejection(&AddVecFx32Into(&delta, &NegateVecFx32Into(otherHalf)), axis);
                VecFx32 toFar = ComputeVectorRejection(&AddVecFx32Into(&delta, otherHalf), axis);
                if (VEC_Mag(&toNear) < VEC_Mag(&toFar)) {
                    normal = NormalizeVectorInto(&toNear);
                } else {
                    normal = NormalizeVectorInto(&toFar);
                }
                extent = cylinder->radius;
                extent += AbsDotProduct(&segmentHalf, &normal);
                if (!func_0203fbb8(extent, &delta, &normal, 2, &result)) {
                    return FALSE;
                }
            }
        }
        if (isCapsule) {
            for (j = 0; j < 2; j++) {
                VecFx32 segmentPoint = j == 0 ? segment->start : segment->end;
                u8 k;
                for (k = 0; k < 2; k++) {
                    VecFx32 cylinderPoint = k == 0 ? cylinder->start : cylinder->end;
                    VecFx32 diff = SubtractVecFx32Into(&segmentPoint, &cylinderPoint);
                    if (IsNearOrigin(&diff)) {
                        func_02041048(&normal, 0x1000, 0, 0);
                    } else {
                        normal = NormalizeVectorInto(&diff);
                    }
                    {
                        fx32 segmentExtent = AbsDotProduct(&segmentHalf, &normal);
                        fx32 cylinderExtent = cylinder->radius + AbsDotProduct(&cylinderHalf, &normal);
                        if (!func_0203fbb8(segmentExtent + cylinderExtent, &delta, &normal, 2, &result)) {
                            return FALSE;
                        }
                    }
                }
            }
        } else {
            normal = cylinderAxis;
            if (!func_0203fbb8(AbsDotProduct(&segmentHalf, &normal) + ComputeDirectionalExtent(cylinder, &cylinderAxis, length * 2, &normal), &delta, &normal, 0, &result)) {
                return FALSE;
            }
        }
    }
    WritePenetrationContact(&result, contact, flags);
    return TRUE;
}
