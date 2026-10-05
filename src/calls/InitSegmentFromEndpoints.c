#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);

void InitSegmentFromEndpoints(CollisionSegment *segment)
{
    VecFx32 delta;

    func_01ff9e3c(&segment->end, &segment->start, &delta);
    segment->direction = delta;
    segment->length = func_01ffaff4(&segment->direction, &segment->direction);
    if (segment->length == 0) {
        VecFx32 down;
        down.x = 0;
        down.y = -FX32_ONE;
        down.z = 0;
        segment->direction = down;
    }
}
