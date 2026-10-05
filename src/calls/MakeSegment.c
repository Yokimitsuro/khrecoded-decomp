#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    VecFx32 start;
    VecFx32 end;
} Segment;

void MakeSegment(Segment *out, const VecFx32 *start, const VecFx32 *end)
{
    Segment segment;

    segment.start = *start;
    segment.end = *end;
    *out = segment;
}
