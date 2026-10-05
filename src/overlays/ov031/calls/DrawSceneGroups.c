#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 hidden;
    u8 slot;
    u8 pad_02[0x6];
    VecFx32 position;
    u8 pad_14[0xc];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x2c];
    s32 scroll;
    u8 pad_30[0x26];
    u8 activeGroupCount;
    u8 pad_57[0x9];
    s32 slotOffsets[1];
    ObjectGroup *groups;
} OverlayState;

typedef struct {
    u8 pad_00[0xa4];
    VecFx32 position;
} SceneSlot;

extern OverlayState *data_ov031_020bc820;
extern SceneSlot *GetActiveSceneSlot(s32 index);
extern void func_01ffb12c(SceneSlot *node);

void DrawSceneGroups(void)
{
    int i;
    SceneSlot *node;
    VecFx32 position;
    int count;

    node = GetActiveSceneSlot(data_ov031_020bc820->groups[0].slot);
    position = data_ov031_020bc820->groups[0].position;
    position.z += data_ov031_020bc820->scroll % 0x3e800;
    for (i = 0; i < 2; i++) {
        node->position = position;
        func_01ffb12c(node);
        position.z -= 0x3e800;
    }
    count = data_ov031_020bc820->activeGroupCount;
    for (i = 1; i < count; i++) {
        ObjectGroup *group = &data_ov031_020bc820->groups[i];
        if (group->hidden == 0
            && group->position.z + data_ov031_020bc820->slotOffsets[group->slot] > -0x32000) {
            node = GetActiveSceneSlot(group->slot);
            node->position = data_ov031_020bc820->groups[i].position;
            func_01ffb12c(node);
        }
    }
}

