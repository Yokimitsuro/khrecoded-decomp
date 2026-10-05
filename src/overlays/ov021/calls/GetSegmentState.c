#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    u8 pad0[0x14];
    VecFx32 end;
    VecFx32 start;
    VecFx32 extra;
} Segment;

typedef struct SegmentState {
    VecFx32 start;
    VecFx32 direction;
    VecFx32 extra;
    int angle;
} SegmentState;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern int AsinToRadians(Segment *segment);

void GetSegmentState(Segment *segment, SegmentState *state)
{
    VecFx32 direction;
    VecFx32 delta;
    VecFx32 temp;

    state->start = segment->start;
    VEC_Subtract(&segment->end, &segment->start, &delta);
    temp = delta;
    VEC_Normalize(&temp, &direction);
    state->direction = direction;
    state->extra = segment->extra;
    state->angle = AsinToRadians(segment);
}
