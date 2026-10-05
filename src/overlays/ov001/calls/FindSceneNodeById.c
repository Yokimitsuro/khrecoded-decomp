#include "nitro/types.h"

typedef struct SceneNode {
    u32 unk_00;
    struct SceneNode *next;
    u8 pad_08[0x48];
    u16 id;
} SceneNode;

typedef struct SceneNodeList {
    u32 unk_00;
    SceneNode *head;
} SceneNodeList;

typedef struct SceneOwner {
    u8 pad_00[0x34];
    SceneNodeList *nodes;
} SceneOwner;

SceneNode *FindSceneNodeById(SceneOwner *owner, u16 id)
{
    SceneNode *node;

    for (node = owner->nodes->head; node != NULL; node = node->next) {
        if (id == node->id) {
            break;
        }
    }
    return node;
}
