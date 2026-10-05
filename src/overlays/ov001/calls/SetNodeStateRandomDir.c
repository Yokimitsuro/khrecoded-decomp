#include "nitro/types.h"

typedef struct SceneNode {
    u8 pad_00[0x2c];
    u8 groupId;
    u8 pad_2D;
    s8 state : 4;
    s8 direction : 4;
    u8 pad_2F;
    u16 timer;
} SceneNode;

extern u32 func_0202a9e4(u32 range);
extern void PlayMenuSoundEffect(u8 groupId);

void SetNodeStateRandomDir(SceneNode *node, int state)
{
    u32 roll;
    int direction;

    node->state = state;
    node->timer = 0;
    roll = func_0202a9e4(2);
    direction = -1;
    if (roll == 0) {
        direction = 1;
    }
    node->direction = direction;
    PlayMenuSoundEffect(node->groupId);
}
