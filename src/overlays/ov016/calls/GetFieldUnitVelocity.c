#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x150];
    VecFx32 velocity;
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
} FieldUnit;

extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);

BOOL GetFieldUnitVelocity(FieldUnit *unit, VecFx32 *out)
{
    FieldActor *actor = ActorRegistry_GetEntityByIndex(unit->actorId);

    *out = actor->velocity;
    if (actor->velocity.x != 0 || actor->velocity.y != 0 || actor->velocity.z != 0) {
        return TRUE;
    }
    return FALSE;
}
