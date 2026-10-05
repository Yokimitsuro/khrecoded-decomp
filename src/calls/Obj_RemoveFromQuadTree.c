#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x104];
    u32 treeOwnerWord;
    u32 node;
} Entity;

extern void QuadTree_RemoveObject(u32 tree, u32 *node);

void Obj_RemoveFromQuadTree(Entity *entity)
{
    if ((entity->flags & 8) == 0) {
        return;
    }
    if ((entity->flags & 0x10) == 0) {
        QuadTree_RemoveObject(**(u32 **)(entity->treeOwnerWord + 4), &entity->node);
    }
    entity->flags = entity->flags & 0xfffffff7;
}
