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

extern u16 GetNextIndex_(const NNSGfdVramTransferTaskQueue *queue, u16 index);extern BOOL IsVramTransferTaskQueueEmpty_(const NNSGfdVramTransferTaskQueue *queue);

BOOL NNSi_GfdPopVramTransferTaskQueue(NNSGfdVramTransferTaskQueue *queue)
{
    if (!IsVramTransferTaskQueueEmpty_(queue)) {
        queue->front = GetNextIndex_(queue, queue->front);
        queue->count--;
        return 1;
    } else {
        return 0;
    }
}