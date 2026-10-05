#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelNode {
    u8 pad_00[0x30];
    u16 flags;
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[4];
    s8 hidden;
    s8 count;
} PanelNode;

typedef struct PanelActor {
    u8 pad_00[4];
    u8 sceneNode[0xa8 - 4];
    VecFx32 position;
} PanelActor;

extern PanelActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void func_01ffb12c(void *node);

void DrawStackedPanels(PanelNode *node)
{
    PanelActor *actor = ActorRegistry_GetEntityByIndex(node->actorId);
    VecFx32 pos = node->position;
    int i;

    node->flags &= 0xffef;
    if (node->hidden & 0x80) {
        return;
    }
    for (i = 0; i < node->count; i++) {
        if (pos.y + 0x1800 > 0) {
            actor->position = pos;
            func_01ffb12c(actor->sceneNode);
            node->flags |= 0x10;
        }
        pos.y += 0x1800;
    }
}
