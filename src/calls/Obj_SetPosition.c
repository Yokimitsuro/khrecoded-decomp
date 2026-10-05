#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0xa4];
    VecFx32 position;
    u8 pad_b4[0x58];
    u8 node[0x18];
} Entity;

extern void func_02033f5c(void *node, const VecFx32 *position);

void Obj_SetPosition(Entity *entity, const VecFx32 *position)
{
    if ((entity->flags & 0x10) == 0) {
        func_02033f5c(entity->node, position);
    }
    entity->position = *position;
}
