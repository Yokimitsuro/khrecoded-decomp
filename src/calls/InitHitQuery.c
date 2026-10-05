#include "nitro/types.h"

typedef struct HitResult {
    s32 distance;
    s32 data[4];
} HitResult;

typedef struct HitQuery {
    s64 minTime;
    s64 maxTime;
    u8 pad_10[0xc];
    HitResult result;
    u8 pad_30;
    u8 hasHit;
} HitQuery;

void InitHitQuery(HitQuery *query)
{
    HitResult initial;

    query->minTime = (s64)0x8000000000000000;
    query->maxTime = 0x7fffffffffffffff;
    initial.distance = 0x7fffffff;
    query->result = initial;
    query->hasHit = FALSE;
}
