#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xb0];
    s32 cacheHandle;
    u8 pad_b4[0xbe - 0xb4];
    u8 lowBits : 4;
    u8 phase : 4;
} FieldUnit;

extern void CacheEntry_SetActive(FieldUnit *unit, BOOL active);

void EnterFieldUnitPhase6(FieldUnit *unit)
{
    unit->phase = 6;
    if (unit->cacheHandle == 0) {
        CacheEntry_SetActive(unit, FALSE);
    }
}
