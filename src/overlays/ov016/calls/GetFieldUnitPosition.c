#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} FieldUnit;

BOOL GetFieldUnitPosition(FieldUnit *unit, VecFx32 *out)
{
    *out = unit->position;
    return TRUE;
}
