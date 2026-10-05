#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 halfLength;
    fx32 radius;
} CollisionCylinder;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
    u8 pad_04[0x18];
    s32 kind;
} SegmentShapeRef;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

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

typedef struct CollisionDisc {
    VecFx32 center;
    fx32 radius;
    VecFx32 normal;
} CollisionDisc;

typedef struct CollisionLine {
    VecFx32 origin;
    VecFx32 direction;
} CollisionLine;

extern const VecFx32 data_0205344c;
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 value);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 ComputeDirectionalExtent(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern BOOL IsVecZero(const VecFx32 *v);
extern VecFx32 GetSegmentHalfDelta(const CollisionSegment *segment);
extern BOOL TestCapsuleAgainstCylinder(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);
extern BOOL func_020405c8(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);
extern VecFx32 ComputeVectorRejection(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 GetSegmentHalfDirection(const CollisionCylinder *cylinder);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern SweepResult func_02047d00(void);
extern VecFx32 SubtractVecFx32Out(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d70(fx32 extent, const VecFx32 *diff, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern fx32 PXI_Init_02047dc0(fx32 value);
extern VecFx32 AddVecFx32Out(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Out(const VecFx32 *v);
extern VecFx32 NormalizeVectorOut(const VecFx32 *v);
extern VecFx32 CrossProductOut(const VecFx32 *a, const VecFx32 *b);
extern BOOL IsNearOrigin_02048ad8(const VecFx32 *v);
extern s32 SignOf(fx32 value);
extern VecFx32 ScaleAxisByDot(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 func_02048b44(const VecFx32 *v, fx32 scale);
extern s32 IntMax(s32 a, s32 b);
extern fx32 SquareFx32_02048b88(fx32 value);
extern fx32 Vec_DotSelf_02048bc0(const VecFx32 *v);
extern void BlendVectorsBySqrtComplementPositive(VecFx32 *a, const VecFx32 *b, fx32 t, VecFx32 *out);
extern CollisionLine MakeSegment(const VecFx32 *origin, const VecFx32 *direction);
extern VecFx32 func_02048c24(const VecFx32 *v, fx32 length);
extern void MultAddOut(VecFx32 *dst, fx32 scale, const VecFx32 *v, const VecFx32 *add);
extern void func_02049720(const VecFx32 *delta, const CollisionDisc *disc, const CollisionLine *line, const VecFx32 *normal, const VecFx32 *perp, const VecFx32 *velocity, fx32 gap, s8 sign, VecFx32 *axis);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 NormalizeIfShort(VecFx32 *v);
extern BOOL func_0204a9f8(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern VecFx32 GetPerpendicularVector(const VecFx32 *v);
extern VecFx32 GetUnitRejectionFromAxis(const VecFx32 *v, const VecFx32 *normal);
extern VecFx32 AverageVecs(s32 count, ...);

BOOL SweepSegmentAgainstCylinder(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    u8 i;
    CollisionSegment *segment = segmentRef->segment;
    CollisionCylinder *cylinder = cylinderRef->cylinder;

    if (!(flags & 4)) {
        SegmentShapeRef swappedRef;
        CollisionSegment moved = *segment;
        moved.end = AddVecFx32Out(&moved.end, velocity);
        swappedRef.segment = &moved;
        if (cylinderRef->kind == 3) {
            return TestCapsuleAgainstCylinder(&swappedRef, cylinderRef, contact, flags & 1);
        }
        return func_020405c8(&swappedRef, cylinderRef, contact, flags & 1);
    }
    {
        BOOL isCapsule = cylinderRef->kind == 3;
        SweepResult result = func_02047d00();
        VecFx32 axis;
        VecFx32 centerA = AverageVecs(2, &segment->start, &segment->end);
        VecFx32 centerB = AverageVecs(2, &cylinder->start, &cylinder->end);
        VecFx32 delta = SubtractVecFx32Out(&centerA, &centerB);
        VecFx32 halfA = GetSegmentHalfDelta(segment);
        VecFx32 halfB = GetSegmentHalfDirection(cylinder);
        VecFx32 dir = NormalizeVectorOut(velocity);
        VecFx32 cross = CrossProductOut(&halfA, &halfB);
        BOOL parallel = IsNearOrigin_02048ad8(&cross);

        if (parallel) {
            VecFx32 sideAxis;
            if (func_0204a9f8(&cylinder->direction, &dir, &sideAxis)) {
                axis = GetUnitRejectionFromAxis(&delta, &cylinder->direction);
            } else {
                VecFx32 normal = NormalizeVectorOut(&sideAxis);
                VecFx32 slide = GetUnitRejectionFromAxis(&dir, &cylinder->direction);
                s32 sign = SignOf(VEC_DotProduct(&slide, &delta));
                VecFx32 offset = ScaleAxisByDot(&delta, &normal);
                VecFx32 along = func_02048b44(&slide, sign * FX_Sqrt(IntMax(SquareFx32_02048b88(cylinder->radius) - Vec_DotSelf_02048bc0(&offset), 0)));
                func_01ff9e0c(&offset, &along, &axis);
                if (IsVecZero(&axis)) {
                    axis = GetPerpendicularVector(&cylinder->direction);
                }
                NormalizeIfShort(&axis);
            }
        } else {
            VEC_Normalize(&cross, &axis);
        }
        if (!func_02047d70(cylinder->radius, &delta, &axis, 0, velocity, &result, NULL)) {
            return FALSE;
        }
        {
            VecFx32 dirA = segment->direction;
            VecFx32 dirB = cylinder->direction;
            fx32 halfLengthB = cylinder->halfLength;

            if (!parallel) {
                const VecFx32 *axes[2];
                const VecFx32 *halves[2];

                axes[0] = &dirA;
                axes[1] = &dirB;
                halves[0] = &halfA;
                halves[1] = &halfB;
                for (i = 0; i < 2; i++) {
                    u8 other = i ^ 1;
                    const VecFx32 *ownAxis = axes[i];
                    VecFx32 side = CrossProductOut(ownAxis, &dir);
                    fx32 extent;

                    if (IsNearOrigin_02048ad8(&side)) {
                        VecFx32 rejA = ComputeVectorRejection(&AddVecFx32Out(&delta, &NegateVecFx32Out(halves[other])), ownAxis);
                        VecFx32 rejB = ComputeVectorRejection(&AddVecFx32Out(&delta, halves[other]), ownAxis);

                        if (VEC_Mag(&rejA) < VEC_Mag(&rejB)) {
                            axis = NormalizeVectorOut(&rejA);
                        } else {
                            axis = NormalizeVectorOut(&rejB);
                        }
                        extent = cylinder->radius;
                    } else {
                        VecFx32 unitSide = NormalizeVectorOut(&side);
                        VecFx32 perp = CrossProductOut(&unitSide, ownAxis);
                        fx32 dist = VEC_DotProduct(&unitSide, &delta);
                        fx32 otherExtent = AbsDotProduct(halves[other], &unitSide);
                        fx32 gap = PXI_Init_02047dc0(dist) - otherExtent;

                        if (gap < 0) {
                            gap = 0;
                        } else if (gap > cylinder->radius) {
                            gap = cylinder->radius;
                        }
                        if (isCapsule || i == 1) {
                            BlendVectorsBySqrtComplementPositive(&unitSide, &perp, FX_Div(gap * -SignOf(dist), cylinder->radius), &axis);
                            extent = cylinder->radius + AbsDotProduct(&halfB, &axis);
                        } else {
                            CollisionDisc disc;

                            disc.radius = cylinder->radius;
                            disc.normal = dirB;
                            func_02049720(&delta, &disc, &MakeSegment(&data_0205344c, &dirA), &unitSide, &perp, velocity, gap, -SignOf(dist), &axis);
                            extent = ComputeDirectionalExtent(cylinder, &dirB, halfLengthB * 2, &axis);
                        }
                    }
                    if (!func_02047d70(extent + AbsDotProduct(&halfA, &axis), &delta, &axis, 2, velocity, &result, NULL)) {
                        return FALSE;
                    }
                }
            }
            if (isCapsule) {
                u8 a;
                u8 j;

                for (a = 0; a < 2; a++) {
                    VecFx32 pointA = (a == 0) ? segment->start : segment->end;

                    for (j = 0; j < 2; j++) {
                        VecFx32 pointB = (j == 0) ? cylinder->start : cylinder->end;
                        VecFx32 diff = SubtractVecFx32Out(&pointA, &pointB);
                        VecFx32 rej = ComputeVectorRejection(&diff, &dir);
                        fx32 dist = VEC_Mag(&rej);
                        fx32 ratio = dist < cylinder->radius ? FX_Div(dist, cylinder->radius) : 0x1000;
                        fx32 height = ratio < 0x1000 ? ComputeOneMinusSquareFraction(ratio) : 0;
                        VecFx32 outward = dist > 0x10 ? func_02048c24(&rej, dist) : data_0205344c;
                        s32 sign = SignOf(VEC_DotProduct(&dir, &diff));

                        axis = func_02048b44(&outward, ratio);
                        if (height != 0) {
                            MultAddOut(&axis, sign * height, &dir, &axis);
                        }
                        if ((a == 0 ? -1 : 1) * VEC_DotProduct(&axis, &segment->direction) < 0 &&
                            (j == 0 ? -1 : 1) * VEC_DotProduct(&axis, &cylinder->direction) > 0) {
                            VEC_Normalize(&axis, &axis);
                            if (!func_02047d70(cylinder->radius, &diff, &axis, 2, velocity, &result, NULL)) {
                                return FALSE;
                            }
                        }
                    }
                }
            } else {
                fx32 extent;

                axis = dirB;
                extent = AbsDotProduct(&halfA, &axis);
                if (!func_02047d70(extent + halfLengthB, &delta, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
        return ResolveSweepContact(&result, contact, flags, velocity);
    }
}
