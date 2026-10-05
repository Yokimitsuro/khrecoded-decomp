#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
} Obj;

typedef struct {
    u8 pad_000[0x150];
    VecFx32 velocity;
} Actor;

extern Actor *ActorRegistry_GetEntityByIndex(u32 id);

BOOL GetActorVelocity_020a2660(Obj *obj, VecFx32 *out)
{
    Actor *actor = ActorRegistry_GetEntityByIndex(obj->actorId);
    *out = actor->velocity;
    if (actor->velocity.x != 0 || actor->velocity.y != 0 || actor->velocity.z != 0) {
        return TRUE;
    }
    return FALSE;
}
