#include "nitro/types.h"

typedef struct HitResult {
    s32 distance;
    s32 data[4];
} HitResult;

void InitMaxDistanceHit(HitResult *result)
{
    HitResult initial;

    initial.distance = 0x7fffffff;
    *result = initial;
}
