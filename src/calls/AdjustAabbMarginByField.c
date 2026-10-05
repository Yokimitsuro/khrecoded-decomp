#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x28];
    fx32 margin;
} Source;

extern void ComputeSegmentBounds(void);
extern void Vec3AddScalar(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar(VecFx32 *v, fx32 amount);

void AdjustAabbMarginByField(Source **handle, VecFx32 *bounds)
{
    Source *source = *handle;

    ComputeSegmentBounds();
    Vec3AddScalar(bounds, source->margin);
    Vec3SubScalar(bounds + 1, source->margin);
}
