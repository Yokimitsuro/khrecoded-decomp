#include "nitro/types.h"

typedef struct SlotInfo {
    u32 flags;
    u8 pad04[0x5c];
} SlotInfo;

typedef struct Target {
    u8 pad00[0x3c];
    s32 slotIndex;
} Target;

typedef struct Limiter Limiter;
typedef int (*LimiterCallback)(Limiter *limiter, Target *target);

struct Limiter {
    u8 pad00[0xc];
    SlotInfo *slots;
    u8 pad10[4];
    u8 remaining;
    u8 pad15[3];
    LimiterCallback callback;
};

int TryConsumeLimitedUse(Limiter *limiter, Target *target)
{
    int result = 0;

    if (limiter->remaining != 0 && (result = limiter->callback(limiter, target)) != 0
        && (limiter->slots[target->slotIndex].flags & 1)) {
        limiter->remaining--;
    }
    return result;
}
