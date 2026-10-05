#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} OrientedBox;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
    u8 pad_04[0x18];
    s32 kind;
} SegmentShapeRef;

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

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern BOOL TestCapsuleAgainstBox(SegmentShapeRef *segmentRef, OrientedBox **boxRef, void *contact, u32 flags);
extern VecFx32 GetSegmentHalfDelta(const CollisionSegment *segment);
extern SweepResult func_02047d00(void);
extern VecFx32 SubtractVecFx32Out(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d70(fx32 extent, const VecFx32 *diff, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern fx32 PXI_Init_02047dc0(fx32 value);
extern VecFx32 AddVecFx32Out(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Out(const VecFx32 *v);
extern void func_0204800c(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 AverageVecs(s32 count, ...);

BOOL SweepObbAgainstSegment(OrientedBox **boxRef, SegmentShapeRef *segmentRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    OrientedBox *box = *boxRef;
    CollisionSegment *segment = segmentRef->segment;

    if (!(flags & 8)) {
        SegmentShapeRef swappedRef;
        CollisionSegment moved = *segment;
        moved.end = AddVecFx32Out(&moved.end, &NegateVecFx32Out(velocity));
        swappedRef.segment = &moved;
        return TestCapsuleAgainstBox(&swappedRef, boxRef, contact, ~flags & 1);
    }
    {
        SweepResult result = func_02047d00();
        VecFx32 axis;
        VecFx32 center = AverageVecs(2, &segment->start, &segment->end);
        VecFx32 diff = SubtractVecFx32Out(&box->center, &center);
        VecFx32 dir = GetSegmentHalfDelta(segment);
        fx32 extent;
        s8 i;
        s8 j;

        for (i = 0; i < 3; i++) {
            axis = box->axes[i];
            extent = box->halfExtents[i];
            if (!func_02047d70(extent + AbsDotProduct(&dir, &axis), &diff, &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
        dir = segment->direction;
        for (i = 0; i < 3; i++) {
            if (AbsDotProduct(&box->axes[i], &dir) <= 0xff0) {
                func_0204800c(&axis, &box->axes[i], &dir);
                extent = 0;
                for (j = 0; j < 3; j++) {
                    if (j != i) {
                        extent += PXI_Init_02047dc0(FX_Mul(VEC_DotProduct(&axis, &box->axes[j]), box->halfExtents[j]));
                    }
                }
                if (!func_02047d70(extent, &diff, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
        return ResolveSweepContact(&result, contact, flags, velocity);
    }
}
