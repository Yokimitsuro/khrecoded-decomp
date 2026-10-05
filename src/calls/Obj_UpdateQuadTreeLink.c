#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x108];
    u32 node;
} Entity;

extern u32 func_0202ef38(u32 *fields, u32 arg);
extern void func_02033f24(u32 tree, u32 *node);

u32 Obj_UpdateQuadTreeLink(u32 world, Entity *entity, u32 arg)
{
    u32 result = 0;

    if (((world != 0) && ((entity->flags & 0x10) == 0)) && ((entity->flags & 8) != 0)) {
        func_02033f24(**(u32 **)(world + 4), &entity->node);
    }
    if (((entity->flags & 0x20) == 0) && ((entity->flags & 0x40) == 0)) {
        result = func_0202ef38(&entity->flags + 1, arg);
    }
    return result;
}
