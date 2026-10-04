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
extern NNSGfdVramTransferTaskQueue sVramTransferTaskQueue;
extern NNSGfdVramTransferTaskQueue sVramTransferTaskQueueState;
extern void ResetTaskQueue_(NNSGfdVramTransferTaskQueue *queue);

void NNS_GfdInitVramTransferManager(NNSGfdVramTransferTask *tasks, u32 capacity)
{
    NNSGfdVramTransferTaskQueue *queue = &sVramTransferTaskQueue;

    queue->tasks = tasks;
    queue->capacity = capacity;
    ResetTaskQueue_(&sVramTransferTaskQueueState);
}