#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
} CollisionHit;

extern void LerpVecFx32Q27InPlace(VecFx32 *point, const VecFx32 *target, fx32 time);

void GetSegmentPointAtHitTime(VecFx32 *out, const CollisionHit *hit, const CollisionSegment *segment)
{
    VecFx32 point;

    if (segment->direction.x == 0 && segment->direction.z == 0) {
        out->x = segment->start.x;
        out->y = (fx32)(((s64)segment->start.y * (0x8000000 - hit->time)) >> 27) + (fx32)(((s64)segment->end.y * hit->time) >> 27);
        out->z = segment->start.z;
        return;
    }
    {
        fx32 time = hit->time;
        point = segment->start;
        LerpVecFx32Q27InPlace(&point, &segment->end, time);
    }
    *out = point;
}
