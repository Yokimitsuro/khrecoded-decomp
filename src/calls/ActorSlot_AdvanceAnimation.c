#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorRegistry ActorRegistry;

typedef struct {
    u8 pad_00[0x10];
    u8 entity[0x1b4];
    s16 animSpeed;
} ActorSlot;

extern u32 Obj_UpdateQuadTreeLink(ActorRegistry *registry, void *entity, fx32 frameStep);
extern ActorRegistry *gActorRegistry;

void ActorSlot_AdvanceAnimation(ActorSlot *slot, fx32 frameStep)
{
    Obj_UpdateQuadTreeLink(gActorRegistry, slot->entity,
                                    (fx32)(((s64)frameStep * slot->animSpeed + 0x800) >> 12));
}
