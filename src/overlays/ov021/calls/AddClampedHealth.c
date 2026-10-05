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

extern void SpawnHealEffect(BigObject *obj);

BOOL AddClampedHealth(BigObject *obj, int delta)
{
    HealthStats *health = obj->health;
    int value = health->current + delta;
    int result = health->max;
    if (value <= result) {
        if (value < 0) {
            value = 0;
        }
        result = value;
    }
    health->current = result;
    if (delta > 0) {
        SpawnHealEffect(obj);
    }
    if (health->current == 0) {
        return TRUE;
    }
    return FALSE;
}
