#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x30];
    u16 flags;
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
} FieldUnit;

extern void *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(void *actor, const VecFx32 *position);
extern void func_ov016_020a25b8(FieldUnit *unit, int arg);

void SetFieldUnitPosition(FieldUnit *unit, const VecFx32 *position)
{
    unit->position = *position;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(unit->actorId), &unit->position);
    if (unit->flags & 4) {
        func_ov016_020a25b8(unit, 0);
    }
}
