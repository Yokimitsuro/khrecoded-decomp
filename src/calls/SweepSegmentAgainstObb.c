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
} CollisionSegment;

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

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void InitHitQuery(SweepResult *result);
extern BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32(VecFx32 *vec);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitHitQuery(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    func_01ff9e3c(a, b, &diff);
    return diff;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

BOOL SweepSegmentAgainstObb(OrientedBox **boxRef, CollisionSegment **segmentRef, void *contact, u32 flags)
{
    CollisionSegment *segment = *segmentRef;
    OrientedBox *box = *boxRef;
    SweepResult result;
    VecFx32 diff;
    VecFx32 dir;
    s8 i;

    if (AreVecsWithinRange16(&segment->start, &segment->end)) {
        return FALSE;
    }
    result = MakeSweepResult();
    diff = VecSub(&segment->start, &box->center);
    dir = VecSub(&segment->end, &segment->start);
    if (flags & 1) {
        NegateVecFx32(&dir);
    }

    if (dir.x == 0 && dir.z == 0 && box->axes[1].x == 0 && box->axes[1].z == 0) {
        if (!SweepIntervalOnAxis(box->halfExtents[1], diff.y * Sign(box->axes[1].y), &box->axes[1], 0, &dir, &result, NULL)) {
            return FALSE;
        }
    } else {
        for (i = 0; i < 3; i++) {
            fx32 extent = box->halfExtents[i];
            if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&box->axes[i], &diff), &box->axes[i], 0, &dir, &result, NULL)) {
                return FALSE;
            }
        }
    }
    return ResolveSweepContact(&result, contact, flags, &dir);
}
