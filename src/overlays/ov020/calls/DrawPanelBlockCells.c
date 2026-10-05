#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ClipBox {
    s32 values[16];
} ClipBox;

typedef struct ClipDesc {
    ClipBox *box;
    u32 extra[7];
} ClipDesc;

typedef struct PanelActor {
    u8 pad_00[4];
    u8 sceneNode[0xa8 - 4];
    VecFx32 position;
    u8 pad_b4[0x130 - 0xb4];
    ClipDesc clip;
} PanelActor;

typedef struct PanelBlock {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[5];
    s8 cellsX;
    s8 cellsY;
    s8 cellsZ;
    fx32 depth;
} PanelBlock;

extern PanelActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void func_01ffb12c(void *node);
extern BOOL TranslateAndFlushGeometry(void *actor, fx32 height, BOOL useActorBuffer);
extern int func_ov021_020af758(ClipDesc *desc, int planes);

void DrawPanelBlockCells(PanelBlock *block)
{
    PanelActor *actor = ActorRegistry_GetEntityByIndex(block->actorId);
    PanelActor *source = ActorRegistry_GetEntityByIndex(block->actorId);
    int z = 0;
    VecFx32 cursor;
    VecFx32 origin;
    fx32 half;
    ClipDesc desc;
    ClipBox box;
    int x;
    int y;

    desc = source->clip;
    box = *source->clip.box;
    desc.box = &box;
    half = (block->depth - 0x1e0) / 2;
    box.values[1] += half;
    box.values[4] -= half;
    if (!func_ov021_020af758(&desc, z)) {
        return;
    }
    origin.x = block->position.x - ((block->cellsX * 0x1800) >> 1) + 0xc00;
    origin.z = block->position.z - ((block->cellsZ * 0x1800) >> 1) + 0xc00;
    origin.y = block->position.y;
    cursor = origin;
    for (; z < block->cellsZ; z++) {
        cursor.y = origin.y;
        for (y = 0; y < block->cellsY; y++) {
            cursor.x = origin.x;
            for (x = 0; x < block->cellsX; x++) {
                actor->position = cursor;
                func_01ffb12c(actor->sceneNode);
                if (y == 0 && block->depth < 0) {
                    TranslateAndFlushGeometry(actor->sceneNode, block->depth, FALSE);
                }
                cursor.x += 0x1800;
            }
            cursor.y += 0x1800;
        }
        cursor.z += 0x1800;
    }
}
