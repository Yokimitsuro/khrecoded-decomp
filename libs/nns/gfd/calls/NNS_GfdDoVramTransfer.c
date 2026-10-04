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
extern NNSGfdVramTransferTask *NNSi_GfdGetFrontVramTransferTaskQueue(NNSGfdVramTransferTaskQueue *queue);
extern int NNSi_GfdPopVramTransferTaskQueue(NNSGfdVramTransferTaskQueue *queue);
extern void Gfd_RunTransferTask(NNSGfdVramTransferTask *task, int flushSource);
extern void DC_StoreAll(void);
extern NNSGfdVramTransferTaskQueue sVramTransferTaskQueue;
extern NNSGfdVramTransferTaskQueue sVramTransferTaskQueueState;

void NNS_GfdDoVramTransfer(void)
{
    NNSGfdVramTransferTaskQueue *queue = &sVramTransferTaskQueue;
    NNSGfdVramTransferTask *task;
    u8 flushSource;

    task = NNSi_GfdGetFrontVramTransferTaskQueue(queue);
    flushSource = sVramTransferTaskQueueState.totalSize < 0x2400;
    if (flushSource == 0) {
        DC_StoreAll();
    }

    if (NNSi_GfdPopVramTransferTaskQueue(queue) != 0) {
        do {
            Gfd_RunTransferTask(task, flushSource);
            queue->totalSize -= task->size;
            task = NNSi_GfdGetFrontVramTransferTaskQueue(queue);
        } while (NNSi_GfdPopVramTransferTaskQueue(queue) != 0);
    }
}