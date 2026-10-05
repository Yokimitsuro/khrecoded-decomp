#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpatialNode {
    u8 pad_00[0x18];
    VecFx32 position;
} SpatialNode;

typedef struct Entity {
    u32 flags;
    u8 pad_04[0xa4];
    VecFx32 position;
    u8 pad_b4[0x54];
    struct World *world;
    SpatialNode node;
} Entity;

typedef struct World {
    u32 pad_00;
    void **tree;
} World;

extern void SetCollisionObjectPosition(SpatialNode *node, const VecFx32 *position);
extern void func_02033c50(void *tree, SpatialNode *node);

void Obj_PlaceInWorld(World *world, Entity *entity, const VecFx32 *position)
{
    if (position == NULL) {
        if (entity->flags & 0x20) {
            position = &entity->node.position;
        } else {
            position = &entity->position;
        }
    }
    if ((entity->flags & 0x10) == 0) {
        SetCollisionObjectPosition(&entity->node, position);
        func_02033c50(*world->tree, &entity->node);
    }
    if ((entity->flags & 0x20) == 0) {
        entity->position = *position;
    }
    entity->world = world;
    entity->flags |= 8;
}
