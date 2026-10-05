#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    VecFx32 velocity;
} FieldUnit;

BOOL InitFieldUnitUpwardVelocity(FieldUnit *unit)
{
    if (!(unit->flags & 0x10000)) {
        unit->velocity.x = 0;
        unit->velocity.y = 0x119a;
        unit->velocity.z = 0;
        unit->flags |= 0x10000;
        return TRUE;
    }
    return FALSE;
}
