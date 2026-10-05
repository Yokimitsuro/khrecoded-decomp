#include "nitro/types.h"

typedef struct TaskBody TaskBody;

struct TaskBody {
    u8 pad_00[4];
    void (*destroy)(TaskBody *body);
    u8 pad_08[9];
    s8 channel;
};

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    TaskBody body;
    u8 pad_1c[0x34];
    u16 id;
} TaskNode;

typedef struct TaskManager {
    u8 pad_00[0x14];
    int usedIdBits[1];
} TaskManager;

extern TaskManager *data_ov001_020a0498;
extern void func_ov001_02068e18(int channel);
extern void ClearPackedBit(int *bitWords, int bitIndex);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

TaskNode *ReleaseTaskNode(TaskNode *node)
{
    TaskBody *body = &node->body;
    TaskManager *manager = data_ov001_020a0498;
    TaskNode *next = node->next;

    if (body->destroy != NULL) {
        body->destroy(body);
    }
    if (node->id < 0xf8 && body->channel >= 0) {
        func_ov001_02068e18(body->channel);
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    ClearPackedBit(manager->usedIdBits, node->id);
    NNSi_FndFreeFromDefaultHeap(node);
    return next;
}
