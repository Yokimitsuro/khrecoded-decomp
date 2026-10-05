#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x47];
    s8 mode;
    u8 pad_48[0x77 - 0x48];
    u8 action;
} FieldUnit;

BOOL IsFieldUnitAction5Mode1(FieldUnit *unit)
{
    if (unit->action == 5) {
        if (unit->mode == 1) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
