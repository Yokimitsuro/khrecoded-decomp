#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *next;
} TaskNode;

typedef struct TaskHost {
    u8 pad_00[0x3c];
    u8 task[0x10];
    TaskNode *activeList;
    u8 pad_50[0x1bf];
    u8 suspended : 1;
    u8 suspendPending : 1;
} TaskHost;

typedef struct Session {
    u8 pad_000[0x20e];
    s16 phase;
} Session;

extern Session *data_ov001_020a0480;
extern TaskHost *data_ov001_020a0484;
extern void func_ov001_0206674c(TaskNode *node);
extern void ActorSlot_UnlinkRoot(void *task);

void SuspendTaskAndSetFlag(void) {
    if (data_ov001_020a0480->phase == ~2) {
        TaskNode *node = data_ov001_020a0484->activeList;
        while (node != NULL) {
            TaskNode *next = node->next;
            func_ov001_0206674c(node);
            node = next;
        }
    }
    if (data_ov001_020a0484->activeList != NULL) {
        ActorSlot_UnlinkRoot(data_ov001_020a0484->task);
    }
    data_ov001_020a0484->suspended = 1;
}
