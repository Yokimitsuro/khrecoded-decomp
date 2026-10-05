#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
} CollisionBox;

typedef struct CollisionCapsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCapsule;

typedef struct BoxShapeRef {
    CollisionBox *box;
} BoxShapeRef;

typedef struct CapsuleShapeRef {
    CollisionCapsule *capsule;
} CapsuleShapeRef;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern BOOL SweepSegmentAgainstObb(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags);
extern PenetrationResult InitMaxDistanceHit(void);
extern VecFx32 AverageVecs(s32 count, ...);
extern VecFx32 SubtractVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetSegmentHalfDelta(const CollisionCapsule *capsule);
extern VecFx32 func_02040010(const VecFx32 *a, const VecFx32 *b);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_0203fbb8(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern int PXI_Init_0203f23c(int value);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestBoxAgainstCapsule(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags)
{
    CollisionCapsule *capsule = capsuleRef->capsule;
    CollisionBox *box = boxRef->box;

    if ((flags & 2) || capsule->length < 16) {
        PenetrationResult result = InitMaxDistanceHit();
        VecFx32 center = AverageVecs(2, &capsule->start, &capsule->end);
        VecFx32 delta = SubtractVecFx32Into(&box->center, &center);
        VecFx32 axis;
        VecFx32 capsuleAxis = GetSegmentHalfDelta(capsule);
        s8 i;
        s8 j;

        for (i = 0; i < 3; i++) {
            fx32 extent;
            axis = box->axes[i];
            extent = box->halfExtents[i];
            if (!func_0203fbb8(extent + AbsDotProduct(&capsuleAxis, &axis), &delta, &axis, 0, &result)) {
                return FALSE;
            }
        }
        if (capsule->length == 0) {
            capsuleAxis.x = 0x1000;
        } else {
            capsuleAxis = capsule->direction;
        }
        for (i = 0; i < 3; i++) {
            if (AbsDotProduct(&box->axes[i], &capsuleAxis) <= 0xFF0) {
                fx32 extent;
                axis = func_02040010(&box->axes[i], &capsuleAxis);
                extent = 0;
                for (j = 0; j < 3; j++) {
                    if (j != i) {
                        extent += PXI_Init_0203f23c(FX_Mul(VEC_DotProduct(&axis, &box->axes[j]), box->halfExtents[j]));
                    }
                }
                if (!func_0203fbb8(extent, &delta, &axis, 0, &result)) {
                    return FALSE;
                }
            }
        }
        WritePenetrationContact(&result, contact, flags);
        return TRUE;
    }
    return SweepSegmentAgainstObb(boxRef, capsuleRef, contact, flags ^ 1);
}
