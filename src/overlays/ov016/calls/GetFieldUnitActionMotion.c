#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x77];
    u8 action;
} FieldUnit;

int GetFieldUnitActionMotion(FieldUnit *unit)
{
    u8 action = unit->action;

    if (action == 6) {
        return 0x12;
    }
    if (action == 11) {
        return 0x13;
    }
    /* actions 12 through 15 share one motion */
    if ((u8)(action + 0xf4) <= 3) {
        return 0x11;
    }
    return 8;
}
