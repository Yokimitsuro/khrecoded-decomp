#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
} PenetrationResult;

BOOL UpdatePenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, PenetrationResult *result)
{
    fx32 overlap;

    if (extent < distance) {
        return FALSE;
    }
    overlap = extent - distance;
    if (result->depth > overlap) {
        result->depth = overlap;
        result->axis = *axis;
        result->axisSign = 1;
        result->featureId = featureId;
    }
    return TRUE;
}
