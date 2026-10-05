#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void UpdateSegmentEndpoint(CollisionSegment *segment)
{
    if (segment->length == 0) {
        VecFx32 down;
        down.x = 0;
        down.y = -FX32_ONE;
        down.z = 0;
        segment->direction = down;
    } else {
        VEC_Normalize(&segment->direction, &segment->direction);
    }
    VEC_MultAdd(segment->length, &segment->direction, &segment->start, &segment->end);
}
