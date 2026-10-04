typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSGfdVramTransferTask {
    u32 type;
    const void *source;
    u32 destination;
    u32 size;
} NNSGfdVramTransferTask;

typedef struct NNSGfdVramTransferTaskQueue {
    NNSGfdVramTransferTask *tasks;
    u32 capacity;
    u16 front;
    u16 rear;
    u16 count;
    u16 padding;
    u32 totalSize;
} NNSGfdVramTransferTaskQueue;
extern BOOL IsVramTransferTaskQueueFull_(const NNSGfdVramTransferTaskQueue *queue);
extern NNSGfdVramTransferTask *NNSi_GfdGetEndVramTransferTaskQueue(NNSGfdVramTransferTaskQueue *queue);
extern void NNSi_GfdPushVramTransferTaskQueue(NNSGfdVramTransferTaskQueue *queue);
extern NNSGfdVramTransferTaskQueue sVramTransferTaskQueue;

BOOL NNS_GfdRegisterNewVramTransferTask(u32 type, u32 destination, const void *source, u32 size)
{
    NNSGfdVramTransferTask *task;
    NNSGfdVramTransferTaskQueue *queue = &sVramTransferTaskQueue;

    if (IsVramTransferTaskQueueFull_(queue) != 0) return 0;
    task = NNSi_GfdGetEndVramTransferTaskQueue(queue);
    task->type = type;
    task->source = source;
    task->destination = destination;
    task->size = size;
    NNSi_GfdPushVramTransferTaskQueue(queue);
    queue->totalSize = queue->totalSize + task->size;
    return 1;
}