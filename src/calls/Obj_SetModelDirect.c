#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 model[0xa4];
    VecFx32 position;
    u8 pad_b4[0x70];
    VecFx32 savedPosition;
} Entity;

extern void func_0202edb0(u8 *model, s32 resource, s32 source, void *extra);

BOOL Obj_SetModelDirect(Entity *entity, s32 resource, s32 source, void *extra)
{
    if (resource != 0) {
        entity->flags &= ~0x20;
        func_0202edb0(entity->model, resource, source, extra);
        if (entity->flags & 8) {
            entity->position = entity->savedPosition;
        }
    }
    return TRUE;
}
