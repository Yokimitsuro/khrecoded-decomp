#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1b0];
    u8 active;
} UnitState;

extern void ResetCountsAndSlots(UnitState *unit);

void ResetUnitCounts(UnitState *unit) {
    unit->active = 0;
    ResetCountsAndSlots(unit);
}
