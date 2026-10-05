#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneNode SceneNode;

typedef struct {
    VecFx32 position;
} ModelDraw;

typedef struct {
    u8 pad_00[0x10];
    u32 entityFlags;
    u8 node[0xa4];
    VecFx32 position;
    u8 pad_c4[0xe4];
    ModelDraw modelDraw;
} ActorSlot;

extern void func_02036b94(ModelDraw *draw);
extern void func_01ffb12c(SceneNode *node);

void ActorSlot_Draw(ActorSlot *slot, BOOL asModel)
{
    if (asModel) {
        slot->modelDraw.position = slot->position;
        func_02036b94(&slot->modelDraw);
        return;
    }
    if (slot->entityFlags & 0x20) {
        return;
    }
    func_01ffb12c((SceneNode *)slot->node);
}
