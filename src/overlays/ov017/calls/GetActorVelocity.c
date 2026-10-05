#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor {
    u8 pad_000[0x150];
    VecFx32 velocity;
} Actor;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
} FieldObject;

extern Actor *ActorRegistry_GetEntityByIndex(u32 actorId);

BOOL GetActorVelocity(FieldObject *object, VecFx32 *velocity)
{
    *velocity = ActorRegistry_GetEntityByIndex(object->actorId)->velocity;
    if (velocity->x != 0 || velocity->y != 0 || velocity->z != 0) {
        return TRUE;
    }
    return FALSE;
}
