#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1b0];
    u8 active;
} UnitState;

extern void func_ov021_020aeb8c(UnitState *unit);

void ResetUnitCounts(UnitState *unit) {
    unit->active = 0;
    func_ov021_020aeb8c(unit);
}
