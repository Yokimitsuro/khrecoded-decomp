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

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx64c FX_DivFx64c(fx32 numerator, fx32 denominator);

BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime)
{
    fx32 speed = VEC_DotProduct(axis, velocity);
    s8 sign;
    int closingSign;
    fx32 absSpeed;
    fx32 relDist;
    s64 enterTime;
    s64 exitTime;

    sign = speed >= 0 ? 1 : -1;
    closingSign = -sign;
    absSpeed = speed * sign;
    relDist = closingSign * distance;

    if (speed >= -1 && speed <= 1) {
        if (relDist < 0) {
            relDist = -relDist;
        }
        if (relDist <= extent) {
            enterTime = (s64)0x8000000000000000LL;
            exitTime = 0x7FFFFFFFFFFFFFFFLL;
            if (relDist >= extent - 2) {
                result->touching = TRUE;
            }
        } else {
            return FALSE;
        }
    } else {
        s64 startDist = relDist - extent;
        if (startDist < -extent) {
            if (relDist < 0) {
                relDist = -relDist;
            }
            if (relDist > extent) {
                return FALSE;
            }
            enterTime = (s64)0x8000000000000000LL;
            exitTime = 0x7FFFFFFFFFFFFFFFLL;
        } else {
            enterTime = FX_DivFx64c(startDist, absSpeed);
            if (enterTime > 0x100000000LL) {
                return FALSE;
            }
            exitTime = enterTime + FX_DivFx64c(extent * 2, absSpeed);
            if (exitTime > 0x100000000LL) {
                exitTime = 0x100000000LL;
            }
        }
    }

    if (result->enterTime < enterTime && enterTime >= 0) {
        result->enterTime = enterTime;
        result->enterAxis = *axis;
        result->enterSign = closingSign;
        result->enterFeature = feature;
    }
    if (exitTime < result->exitTime) {
        result->exitTime = exitTime;
    }
    if (enterTime <= 0) {
        fx32 depth = extent - (distance < 0 ? -distance : distance);
        if (result->minDepth > depth) {
            result->minDepth = depth;
            result->depthAxis = *axis;
            result->depthSign = distance == 0 ? 0 : (distance > 0 ? 1 : -1);
            result->depthFeature = feature;
        }
    }
    if (outTime != NULL) {
        *outTime = enterTime;
    }
    return TRUE;
}
