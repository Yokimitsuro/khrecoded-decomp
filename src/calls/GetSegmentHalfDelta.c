#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    VecFx32 start;
    VecFx32 end;
} Segment;

extern void GetSegmentDelta(VecFx32 *out, const Segment *segment);

void GetSegmentHalfDelta(VecFx32 *out, const Segment *segment)
{
    VecFx32 half;
    VecFx32 delta;

    GetSegmentDelta(&delta, segment);
    half = delta;
    half.x >>= 1;
    half.y >>= 1;
    half.z >>= 1;
    *out = half;
}
