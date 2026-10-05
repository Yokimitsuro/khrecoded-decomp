#include "nitro/types.h"

typedef struct FieldTask {
    u8 pad_00[0x11];
    s8 linkA;
    s8 linkB;
    u8 pad_13[0x1d];
} FieldTask;

typedef struct TaskNode TaskNode;

struct TaskNode {
    TaskNode *prev;
    TaskNode *next;
    FieldTask task;
    u8 pad_38[0x18];
    u16 id;
    u8 pad_52;
    u8 config;
};

typedef struct TriggerQueue {
    u8 pad_00[0x14];
    int usedBits[8];
    TaskNode *head;
} TriggerQueue;

extern TriggerQueue *data_ov001_020a0498;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void MIi_CpuClear32(u32 value, void *dest, u32 size);
extern void SetPackedBit(int *bitWords, int bitIndex);
extern void InitRangeTriggerNode(FieldTask *task, void *params);
extern void InitOffsetFieldTask(FieldTask *task, void *params);
extern void InitBitChainTrigger(FieldTask *task, void *params);
extern void InitModeFieldTask(FieldTask *task, void *params);
extern void InitModeFieldTask_02069c8c(FieldTask *task, void *params);
extern void InitFieldTask(FieldTask *task, void *params);
extern void InitPairFieldTask(FieldTask *task, void *params);
extern void InitModeFieldTask_02069f04(FieldTask *task, void *params);
extern void InitTaskCallbacks(FieldTask *task, void *params);

void CreateFieldTaskNode(u32 id, BOOL isSecondary, int type, void *params)
{
    TriggerQueue *queue = data_ov001_020a0498;
    TaskNode *node;
    TaskNode *tail;
    FieldTask *task;

    if (isSecondary) {
        id += 0xf8;
    }
    node = NNSi_FndAllocFromDefaultHeap(sizeof(TaskNode));
    MIi_CpuClearFast(0, node, sizeof(TaskNode));
    SetPackedBit(queue->usedBits, id);
    tail = queue->head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    node->prev = tail;
    task = &node->task;
    MIi_CpuClear32(0, task, sizeof(FieldTask));
    task->linkA = -1;
    task->linkB = -1;
    switch (type) {
    case 0:
        InitRangeTriggerNode(task, params);
        break;
    case 1:
        InitOffsetFieldTask(task, params);
        break;
    case 2:
        InitBitChainTrigger(task, params);
        break;
    case 3:
        InitModeFieldTask(task, params);
        break;
    case 4:
        InitModeFieldTask_02069c8c(task, params);
        break;
    case 6:
        InitFieldTask(task, params);
        break;
    case 7:
        InitPairFieldTask(task, params);
        break;
    case 8:
        InitModeFieldTask_02069f04(task, params);
        break;
    case 9:
        InitTaskCallbacks(task, params);
        break;
    }
    node->config |= 1;
    node->id = id;
}
