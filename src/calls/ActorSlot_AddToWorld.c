#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorRegistry ActorRegistry;

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[6];
    u8 entity[0xa8];
    VecFx32 position;
} ActorSlot;

extern void Obj_PlaceInWorld(ActorRegistry *registry, void *entity, VecFx32 *position);
extern ActorRegistry *gActorRegistry;

void ActorSlot_AddToWorld(ActorSlot *slot)
{
    Obj_PlaceInWorld(gActorRegistry, slot->entity, &slot->position);
    slot->flags |= 0x100;
}
