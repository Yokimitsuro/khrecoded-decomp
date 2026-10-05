#include "nitro/fx_types.h"

extern void ComputeSegmentBounds(void);
extern void Vec3AddScalar(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar(VecFx32 *v, fx32 amount);

void AdjustAabbMargin(u32 unused, VecFx32 *bounds)
{
    ComputeSegmentBounds();
    Vec3AddScalar(bounds, 0x10);
    Vec3SubScalar(bounds + 1, 0x10);
}
