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

extern void func_02035594(ActorRegistry *registry, void *entity, VecFx32 *position);
extern ActorRegistry *data_0206083c;

void ActorSlot_AddToWorld(ActorSlot *slot)
{
    func_02035594(data_0206083c, slot->entity, &slot->position);
    slot->flags |= 0x100;
}
