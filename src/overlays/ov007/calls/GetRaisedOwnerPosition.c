#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity {
    u8 pad_00[0x40];
    VecFx32 raisedPosition;
} Entity;

extern VecFx32 *func_ov007_020a100c(Entity *entity);

VecFx32 *GetRaisedOwnerPosition(Entity *entity)
{
    entity->raisedPosition = *func_ov007_020a100c(entity);
    entity->raisedPosition.y += 0x800;
    return &entity->raisedPosition;
}
