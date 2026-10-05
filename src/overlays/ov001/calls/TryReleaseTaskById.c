#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    u8 pad_08[0x39];
    s8 locked;
} TaskNode;

typedef struct TaskManager TaskManager;

extern TaskManager *data_ov001_020a0498;
extern TaskNode *FindSceneNodeById(TaskManager *manager, u16 id);
extern TaskNode *ReleaseTaskNode(TaskNode *node);

BOOL TryReleaseTaskById(int id)
{
    TaskManager *manager = data_ov001_020a0498;

    if (FindSceneNodeById(manager, id)->locked != 0) {
        return FALSE;
    }
    ReleaseTaskNode(FindSceneNodeById(manager, id));
    return TRUE;
}
