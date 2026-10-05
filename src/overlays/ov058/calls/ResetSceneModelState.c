#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 active;
} SceneModel;

typedef struct {
    u8 enabled;
    u8 pad_001[3];
    s32 timer;
    u8 pad_008[0x30 - 0x8];
    s32 phase;
    u8 pad_034[0x174 - 0x34];
    SceneModel frontNode;
    SceneModel models[3];
    SceneModel backNode;
} SceneModelBlock;

extern SceneModelBlock data_ov058_020d8a44;

extern void StopSeqArcOrDefault(int seqArcNo, int unused1, int unused2);
extern BOOL Camera_ReturnFromPathView(void);

void ResetSceneModelState(void)
{
    SceneModelBlock *block = &data_ov058_020d8a44;
    int i;

    block->timer = 0;
    block->frontNode.active = 0;
    block->backNode.active = 0;
    for (i = 0; i < 3; i++) {
        block->models[i].active = 0;
    }
    block->phase = 0;
    block->enabled = 0;
    StopSeqArcOrDefault(0xc2, 0, 0);
    Camera_ReturnFromPathView();
}
