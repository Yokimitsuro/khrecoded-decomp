#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
} PenetrationResult;

BOOL UpdateSignedPenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, PenetrationResult *result)
{
    s32 sign;
    fx32 overlap;

    if (distance == 0) {
        sign = 0;
    } else {
        sign = distance > 0 ? 1 : -1;
    }
    if (extent < distance * sign) {
        return FALSE;
    }
    overlap = extent - distance * sign;
    if (result->depth > overlap) {
        result->depth = overlap;
        result->axis = *axis;
        result->axisSign = sign;
        result->featureId = featureId;
    }
    return TRUE;
}
