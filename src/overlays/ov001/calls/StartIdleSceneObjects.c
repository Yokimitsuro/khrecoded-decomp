#include "nitro/types.h"

typedef struct SceneNode SceneNode;

struct SceneNode {
    SceneNode *next;
    u8 pad_04[0x2a];
    s8 state : 4;
    s8 stateHigh : 4;
    u8 isHidden : 1;
    u8 isRunning : 1;
    u8 nodeFlags : 6;
};

typedef struct SceneContext {
    u8 pad_000[0x4c];
    SceneNode *nodes;
    u8 pad_050[0x1bf];
    u8 flags;
} SceneContext;

extern SceneContext *data_ov001_020a0484;
extern void SetNodeStateRandomDir(SceneNode *node, int mode);

void StartIdleSceneObjects(void)
{
    SceneContext *scene = data_ov001_020a0484;
    SceneNode *node;

    for (node = scene->nodes; node != NULL; node = node->next) {
        if (!node->isRunning && node->state < 0 && !node->isHidden) {
            SetNodeStateRandomDir(node, 0);
        }
    }
    scene->flags |= 2;
}
