#include "nitro/types.h"

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    u8 pad_08[0x48];
    u16 id;
} TaskNode;

typedef struct TaskManager {
    u16 activeIds[8];
    u8 activeCount;
    u8 pad_11[0x23];
    TaskNode *head;
} TaskManager;

extern TaskManager *data_ov001_020a0498;
extern TaskNode *ReleaseTaskNode(TaskNode *node);
extern void MIi_CpuClear16(u32 value, void *dest, u32 size);

void ReleaseLowIdTaskNodes(void)
{
    TaskNode *node = data_ov001_020a0498->head->next;

    while (node != NULL) {
        if (node->id >= 0xf8) {
            node = node->next;
        } else {
            node = ReleaseTaskNode(node);
        }
    }
    MIi_CpuClear16(0xffff, data_ov001_020a0498->activeIds, sizeof(data_ov001_020a0498->activeIds));
    data_ov001_020a0498->activeCount = 0;
}
