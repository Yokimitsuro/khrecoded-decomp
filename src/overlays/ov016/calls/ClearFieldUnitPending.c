#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xd8];
    u32 pending : 1;
    u32 otherFlags : 31;
} FieldUnit;

void ClearFieldUnitPending(FieldUnit *unit)
{
    if (unit->pending) {
        unit->pending = 0;
    }
}
