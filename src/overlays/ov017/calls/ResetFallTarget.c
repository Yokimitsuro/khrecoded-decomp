#include "nitro/types.h"

typedef struct FallTarget {
    u8 active;
    s8 group;
    s16 index;
    s32 timer;
} FallTarget;

void ResetFallTarget(FallTarget *target)
{
    target->active = 1;
    target->group = -1;
    target->index = -1;
    target->timer = -1;
}
