#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SweepResult SweepResult;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL ClipRayAgainstPlane(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);

BOOL SweepAlongProjectedAxis(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime)
{
    return ClipRayAgainstPlane(extent, VEC_DotProduct(axis, offset), axis, feature, velocity, result, outTime);
}
