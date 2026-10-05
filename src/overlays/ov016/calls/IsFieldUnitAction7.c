#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x77];
    u8 action;
} FieldUnit;

BOOL IsFieldUnitAction7(FieldUnit *unit)
{
    if (unit->action == 7) {
        return TRUE;
    }
    return FALSE;
}
