#include "nitro/types.h"

typedef struct {
    u8 pad_000[2];
    s8 state;
    u8 pad_003[0x2d];
    u8 node[0x124];
} SceneEntry;

typedef struct {
    u8 pad_00[8];
    SceneEntry *entries;
    u8 pad_0c[9];
    u8 entryCount;
    u8 pad_16[0x2a];
    s8 flags;
    u8 pad_41[3];
    u16 mainNode[1];
} SceneGroup;

extern void func_ov021_020ae944(void *node, int material, int polygonId);
extern void func_ov021_020ae8ac(u16 *node);

void AssignSceneGroupPolygonIds(SceneGroup *group)
{
    int i = 0;
    int polygonId = 0;

    for (; i < group->entryCount; i++) {
        SceneEntry *entry = &group->entries[i];
        if (entry->state != -1) {
            func_ov021_020ae944(entry->node, 1, polygonId + 0xd);
            polygonId++;
            if (polygonId > 0xf) {
                polygonId = 0;
            }
        }
    }
    if (group->flags & 1) {
        func_ov021_020ae8ac(group->mainNode);
    }
}
