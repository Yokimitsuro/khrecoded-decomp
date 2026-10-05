#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct CollisionObject {
    u8 pad_00[0x24];
    CollisionShape shape;
    u8 pad_44[0x44];
} CollisionObject;

typedef struct Entity {
    u32 flags;
    u8 node[0x108];
    CollisionObject collision;
} Entity;

typedef struct Owner {
    u8 pad_00[0x10];
    u8 quadTreeNode[4];
} Owner;

typedef struct Block {
    u8 pad_00[8];
    Owner *owner;
    u8 pad_0c[4];
    CollisionShape shape;
    u8 pad_30[2];
    u8 entityId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0xc];
    s8 state;
    u8 pad_51;
    s8 cooldown;
    u8 pad_53;
    u16 flags;
    u8 pad_56[6];
    fx32 groundY;
    fx32 heightOffset;
} Block;

extern Entity *ActorRegistry_GetEntityByIndex(u32 id);
extern void Obj_SetPosition(Entity *entity, const VecFx32 *position);
extern void Obj_RemoveFromQuadTree(void *entity);
extern void ResizeBoxCollisionObject(CollisionObject *object, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern void BuildCollisionShape(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern BOOL IsEntityWithinRange(Block *block);
extern Block *func_ov020_020a2898(Block *block);
extern int UpdatePanelAnimations(Block *block);

int UpdateStackedBlock(Block *block)
{
    Block *support;
    Entity *entity;
    fx32 height;

    if (block->flags & 8) {
        return 0;
    }
    block->heightOffset = 0;
    if (block->cooldown > 0) {
        block->cooldown--;
    }
    if (block->flags & 2) {
        block->position.y -= 0x600;
        if (block->position.y <= block->groundY) {
            block->position.y = block->groundY;
            block->flags &= 0xFFFD;
            BuildCollisionShape(&block->shape, &block->position, 3, 0x1800, 0x1800, 0x1800, 0, 0, -1);
            block->cooldown = 4;
        }
        Obj_SetPosition(ActorRegistry_GetEntityByIndex(block->entityId), &block->position);
    }
    if (block->flags & 4) {
        support = func_ov020_020a2898(block);
        if (support == NULL) {
            Obj_RemoveFromQuadTree(block->owner->quadTreeNode);
            block->heightOffset = 0;
            block->flags &= 0xFFFB;
        } else {
            if (!(support->flags & 2)) {
                block->flags &= 0xFFFB;
            }
            entity = ActorRegistry_GetEntityByIndex(block->entityId);
            height = support->position.y + 0x1800 - block->position.y;
            block->heightOffset = entity->collision.shape.bounds[1] - entity->collision.shape.bounds[4] - height;
            ResizeBoxCollisionObject(&entity->collision, 0x1800, height, 0x1800, 0);
            Obj_SetPosition(entity, &block->position);
        }
    }
    if (block->state == 1) {
        return UpdatePanelAnimations(block);
    }
    if (block->state == 0) {
        ActorSlot_SetFlag8ByIndex(block->entityId, IsEntityWithinRange(block));
    }
    return 0;
}
