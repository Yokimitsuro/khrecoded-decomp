#include "nitro/types.h"

typedef struct HealthStats {
    u16 pad0;
    u16 current;
    u16 max;
} HealthStats;

typedef struct BigObject {
    u8 pad_000[0x1d4];
    HealthStats *health;
} BigObject;

extern s32 func_ov021_020a7670(BigObject *obj, s32 value);
extern BOOL AddClampedHealth(BigObject *obj, int delta);

void ApplyScaledHealthDelta(BigObject *obj, s32 amount, BOOL force)
{
    s32 scaled = func_ov021_020a7670(obj, amount);
    if (obj->health->current != 0 || force) {
        AddClampedHealth(obj, (s16)((scaled + 0xfff) >> 12));
    }
}
