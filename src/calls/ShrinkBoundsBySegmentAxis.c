#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
    u8 pad_18[0x10];
    fx32 scale;
} Segment;

typedef struct {
    VecFx32 low;
    VecFx32 high;
} Bounds;

extern void ComputeSegmentBounds(Segment **segmentRef, Bounds *bounds);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

void ShrinkBoundsBySegmentAxis(Segment **segmentRef, Bounds *bounds)
{
    Segment *segment = *segmentRef;
    VecFx32 extent;
    VecFx32 dir;
    VecFx32 delta;

    ComputeSegmentBounds(segmentRef, bounds);
    func_01ff9e3c(&segment->end, &segment->start, &delta);
    dir = delta;
    VEC_Normalize(&dir, &dir);
    extent.x = ComputeOneMinusSquareFraction(dir.x);
    extent.y = ComputeOneMinusSquareFraction(dir.y);
    extent.z = ComputeOneMinusSquareFraction(dir.z);
    ScaleVecFx32InPlace(&extent, segment->scale);
    func_01ff9e0c(&bounds->low, &extent, &bounds->low);
    func_01ff9e3c(&bounds->high, &extent, &bounds->high);
}
