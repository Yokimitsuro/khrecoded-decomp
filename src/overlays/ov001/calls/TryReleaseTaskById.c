#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    u8 pad_08[0x39];
    s8 locked;
} TaskNode;

typedef struct TaskManager TaskManager;

extern TaskManager *data_ov001_020a0498;
extern TaskNode *func_ov001_02069014(TaskManager *manager, u16 id);
extern TaskNode *ReleaseTaskNode(TaskNode *node);

BOOL TryReleaseTaskById(int id)
{
    TaskManager *manager = data_ov001_020a0498;

    if (func_ov001_02069014(manager, id)->locked != 0) {
        return FALSE;
    }
    ReleaseTaskNode(func_ov001_02069014(manager, id));
    return TRUE;
}
