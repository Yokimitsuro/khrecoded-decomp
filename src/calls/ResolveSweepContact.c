#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct SweepContact {
    fx32 depth;
    VecFx32 normal;
    s32 time;
    u8 feature;
} SweepContact;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void NegateVecFx32(VecFx32 *vec);

static inline VecFx32 SignedAxis(const VecFx32 *axis, s8 sign)
{
    VecFx32 result = *axis;
    if (sign < 0) {
        NegateVecFx32(&result);
    }
    return result;
}

static inline void CopyVec(VecFx32 *dst, const VecFx32 *src)
{
    *dst = *src;
}

static inline VecFx32 NormalizedWithLength(const VecFx32 *v, fx32 *length)
{
    VecFx32 out;
    *length = func_01ffaff4(v, &out);
    return out;
}

BOOL ResolveSweepContact(SweepResult *result, SweepContact *contact, u32 flags, const VecFx32 *velocity)
{
    if (result->exitTime < result->enterTime) {
        return FALSE;
    }
    if (result->enterTime < 0) {
        VecFx32 axis;
        VecFx32 normal = SignedAxis(&result->depthAxis, result->depthSign);
        fx32 approach;
        CopyVec(&axis, &normal);
        approach = VEC_DotProduct(velocity, &axis);
        if (result->minDepth < approach) {
            return FALSE;
        }
        if (contact != NULL) {
            contact->depth = result->minDepth - approach;
            contact->time = -1;
            contact->normal = normal;
            contact->feature = result->depthFeature;
        }
    } else if (result->touching) {
        return FALSE;
    } else {
        VecFx32 axis;
        VecFx32 normal = SignedAxis(&result->enterAxis, result->enterSign);
        VecFx32 direction;
        fx32 length;
        fx32 dot;
        fx32 travel;
        CopyVec(&axis, &normal);
        direction = NormalizedWithLength(velocity, &length);
        dot = VEC_DotProduct(&direction, &axis);
        travel = (fx32)(((0x100000000LL - result->enterTime) * length + 0x80000000LL) >> 32);
        if (travel != 0) {
            travel = (fx32)(((s64)travel * -dot + 0x800) >> 12);
        }
        if (travel < 0) {
            return FALSE;
        }
        if (contact != NULL) {
            contact->time = (s32)(*(u64 *)&result->enterTime >> 5);
            contact->depth = travel;
            contact->normal = normal;
            contact->feature = result->enterFeature;
        }
    }
    if (contact != NULL && (flags & 1)) {
        NegateVecFx32(&contact->normal);
        contact->feature = (contact->feature & ~3) | ((contact->feature & 1) << 1) | ((contact->feature & 2) >> 1);
    }
    return TRUE;
}
