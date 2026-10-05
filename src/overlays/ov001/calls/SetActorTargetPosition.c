#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorMover {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} ActorMover;

extern void *ActorRegistry_GetEntityByIndex(u32 id);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void SetActorTargetPosition(ActorMover *mover, const VecFx32 *position)
{
    mover->position = *position;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(mover->actorId), &mover->position);
}
