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

typedef struct Basis3x3 {
    VecFx32 row[3];
} Basis3x3;

extern PenetrationResult InitMaxDistanceHit(void);
extern VecFx32 AverageVecs(s32 count, ...);
extern VecFx32 SubtractVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetSegmentHalfVector(const CollisionCylinder *cylinder);
extern VecFx32 GetSegmentHalfDirection(const CollisionCylinder *cylinder);
extern VecFx32 ComputeCrossProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL IsNearOrigin(const VecFx32 *vec);
extern VecFx32 NormalizeVectorInto(const VecFx32 *vec);
extern VecFx32 ComputeVectorRejection(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 GetPerpendicularVector(const VecFx32 *vec);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern BOOL func_0203fbb8(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern VecFx32 NegateVecFx32Into(const VecFx32 *vec);
extern VecFx32 AddVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag(const VecFx32 *vec);
extern VecFx32 NormalizeVecFx32Out(const VecFx32 *vec);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern VecFx32 VecFx32ScaledCopy(const VecFx32 *vec, fx32 scale);
extern VecFx32 MultAddVecFx32Out(fx32 scale, const VecFx32 *vec, const VecFx32 *add);
extern int NormalizeIfShort(VecFx32 *vec);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 ComputeDirectionalExtent(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern VecFx32 GetUnitRejectionFromAxis(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NormalizeVectorAltInto(const VecFx32 *vec);
extern VecFx32 func_02040010(const VecFx32 *a, const VecFx32 *b);
extern Basis3x3 BuildMatrix33(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 TransformVectorByBasisOut(const VecFx32 *vec, const Basis3x3 *basis);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int PXI_Init_0203f23c(int value);
extern s32 MinFx32(s32 a, s32 b);
extern int Sign(fx32 value);
extern fx32 SquareFx32ToFx64(fx32 value);
extern fx32 FX_Sqrt(fx32 value);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestCylinderAgainstCylinder(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags)
{
    CollisionCylinder *cylA = refA->cylinder;
    CollisionCylinder *cylB = refB->cylinder;
    BOOL isCapsule = refA->kind == 3;
    fx32 radiusB;
    fx32 radiusA;
    fx32 extent;
    BOOL parallel;
    fx32 halfLengthB;
    u8 j;
    fx32 halfLengthA;
    u8 i;
    u8 k;
    PenetrationResult result = InitMaxDistanceHit();
    VecFx32 centerA = AverageVecs(2, &cylA->start, &cylA->end);
    VecFx32 centerB = AverageVecs(2, &cylB->start, &cylB->end);

    radiusA = cylA->radius;
    radiusB = cylB->radius;
    VecFx32 delta = SubtractVecFx32Into(&centerA, &centerB);
    VecFx32 halfA = GetSegmentHalfVector(cylA);
    VecFx32 halfB = GetSegmentHalfDirection(cylB);
    VecFx32 axis;
    VecFx32 cross = ComputeCrossProduct(&halfA, &halfB);

    parallel = IsNearOrigin(&cross);
    if (parallel) {
        axis = ComputeVectorRejection(&delta, &NormalizeVectorInto(&halfA));
        if (IsNearOrigin(&axis)) {
            axis = GetPerpendicularVector(&halfA);
        }
    } else {
        axis = cross;
    }
    VEC_Normalize(&axis, &axis);
    if (!func_0203fbb8(radiusA + radiusB, &delta, &axis, 0, &result)) {
        return FALSE;
    }
    {
        VecFx32 axisA = cylA->direction;
        VecFx32 axisB = cylB->direction;

        halfLengthA = cylA->length / 2;
        halfLengthB = cylB->length / 2;
        if (!parallel) {
            const VecFx32 *axes[2];
            const VecFx32 *halves[2];

            axes[0] = &axisA;
            axes[1] = &axisB;
            halves[0] = &halfA;
            halves[1] = &halfB;
            for (i = 0; i < 2; i++) {
                VecFx32 rejA = ComputeVectorRejection(&AddVecFx32Into(&delta, &NegateVecFx32Into(halves[(u8)(i ^ 1)])), axes[i]);
                VecFx32 rejB = ComputeVectorRejection(&AddVecFx32Into(&delta, halves[(u8)(i ^ 1)]), axes[i]);

                if (VEC_Mag(&rejA) < VEC_Mag(&rejB)) {
                    axis = NormalizeVecFx32Out(&rejA);
                } else {
                    axis = NormalizeVecFx32Out(&rejB);
                }
                if (!isCapsule || i == 0) {
                    VecFx32 unitCross = NormalizeVectorInto(&cross);
                    VecFx32 side = ComputeCrossProduct(&unitCross, axes[i]);
                    fx32 cosine = VEC_DotProduct(&axisB, axes[i]);
                    fx32 crossWeight = VEC_DotProduct(&axis, &unitCross);
                    fx32 sideWeight = VEC_DotProduct(&axis, &side);

                    axis = VecFx32ScaledCopy(&unitCross, FX_Mul(crossWeight, cosine));
                    axis = MultAddVecFx32Out(sideWeight, &side, &axis);
                    NormalizeIfShort(&axis);
                }
                if (isCapsule) {
                    extent = cylA->radius + AbsDotProduct(&halfA, &axis);
                } else {
                    extent = ComputeDirectionalExtent(cylA, &axisA, halfLengthA * 2, &axis);
                }
                extent += ComputeDirectionalExtent(cylB, &axisB, halfLengthB * 2, &axis);
                if (!func_0203fbb8(extent, &delta, &axis, 3, &result)) {
                    return FALSE;
                }
            }
        }
        for (k = 0; k < 2; k++) {
            axis = (k == 0) ? axisB : axisA;
            if (isCapsule) {
                extent = cylA->radius + AbsDotProduct(&halfA, &axis);
            } else if (k == 0) {
                extent = ComputeDirectionalExtent(cylA, &axisA, halfLengthA * 2, &axis);
            } else {
                extent = halfLengthA;
            }
            if (k == 1) {
                extent += ComputeDirectionalExtent(cylB, &axisB, halfLengthB * 2, &axis);
            } else {
                extent += halfLengthB;
            }
            if (!func_0203fbb8(extent, &delta, &axis, 0, &result)) {
                return FALSE;
            }
            if (isCapsule) {
                break;
            }
        }
        for (i = 0; i < 2; i++) {
            VecFx32 pointA = (i == 0) ? cylA->start : cylA->end;

            for (j = 0; j < 2; j++) {
                VecFx32 pointB = (j == 0) ? cylB->start : cylB->end;
                VecFx32 diff = SubtractVecFx32Into(&pointA, &pointB);

                if (isCapsule) {
                    VecFx32 toAxis = GetUnitRejectionFromAxis(&diff, &axisB);
                    VecFx32 offset = MultAddVecFx32Out(-cylB->radius, &toAxis, &diff);

                    axis = NormalizeVectorAltInto(&offset);
                } else {
                    VecFx32 normal = func_02040010(&axisA, &axisB);
                    VecFx32 inPlaneA = func_02040010(&normal, &axisA);
                    VecFx32 inPlaneB = func_02040010(&normal, &axisB);
                    Basis3x3 basis = BuildMatrix33(&axisA, &normal);
                    VecFx32 local = TransformVectorByBasisOut(&inPlaneB, &basis);
                    VecFx32 rimPoint;
                    VecFx32 toRim;
                    fx32 dist = VEC_DotProduct(&diff, &inPlaneA) - FX_Div(FX_Mul(VEC_DotProduct(&diff, &axisA), local.x), local.y);
                    fx32 clamped = MinFx32(PXI_Init_0203f23c(dist), cylA->radius);

                    rimPoint = VecFx32ScaledCopy(&inPlaneA, Sign(dist) * clamped);
                    rimPoint = MultAddVecFx32Out(Sign(VEC_DotProduct(&diff, &normal)) * FX_Sqrt(SquareFx32ToFx64(cylA->radius) - SquareFx32ToFx64(clamped)), &normal, &rimPoint);
                    toRim = SubtractVecFx32Into(&rimPoint, &diff);
                    {
                        VecFx32 tangentA = ComputeCrossProduct(&rimPoint, &axisA);
                        VecFx32 tangentB = ComputeCrossProduct(&toRim, &axisB);

                        axis = func_02040010(&tangentA, &tangentB);
                    }
                }
                if (isCapsule) {
                    extent = cylA->radius + AbsDotProduct(&halfA, &axis);
                } else {
                    extent = ComputeDirectionalExtent(cylA, &axisA, halfLengthA * 2, &axis);
                }
                extent += ComputeDirectionalExtent(cylB, &axisB, halfLengthB * 2, &axis);
                if (!func_0203fbb8(extent, &delta, &axis, 3, &result)) {
                    return FALSE;
                }
            }
        }
    }
    WritePenetrationContact(&result, contact, flags);
    return TRUE;
}
