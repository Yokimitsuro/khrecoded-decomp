typedef unsigned short u16;
typedef unsigned int u32;

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
NNSGfdVramTransferTask *NNSi_GfdGetEndVramTransferTaskQueue(NNSGfdVramTransferTaskQueue *queue)
{
    return &queue->tasks[queue->rear];
}