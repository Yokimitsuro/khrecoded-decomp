#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xbe];
    u8 lowBits : 4;
    u8 phase : 4;
} FieldUnit;

BOOL HasFieldUnitPhase(FieldUnit *unit)
{
    if (unit->phase != 0) {
        return TRUE;
    }
    return FALSE;
}
