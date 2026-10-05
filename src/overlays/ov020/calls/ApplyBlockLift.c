#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Block {
    u8 pad_00[0x10];
    u8 shape[0x22];
    u8 entityId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0x1c];
    fx32 lift;
} Block;

extern void *ActorRegistry_GetEntityByIndex(u32 id);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void func_ov001_0208085c(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY,
                                         fx32 sizeZ, s32 angle, BOOL allocate, int mode);

void ApplyBlockLift(Block *block, fx32 lift)
{
    block->lift = lift;
    if (lift == 0) {
        return;
    }
    block->position.y += lift;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(block->entityId), &block->position);
    func_ov001_0208085c(block->shape, &block->position, 3, 0x1800, 0x1800, 0x1800, 0, 0, -1);
}
