typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NNSGfdVramTransferTask NNSGfdVramTransferTask;

typedef struct NNSGfdVramTransferTaskQueue {
    NNSGfdVramTransferTask *pTaskArray;
    u32 lengthOfArray;
    u16 idxFront;
    u16 idxRear;
    u16 numTasks;
    u16 pad16_;
    u32 totalSize;
} NNSGfdVramTransferTaskQueue;

extern NNSGfdVramTransferTaskQueue data_0205a8d0;
extern NNSGfdVramTransferTaskQueue data_0205a8d0_budget;
extern void func_02013f34(NNSGfdVramTransferTaskQueue *queue);

void GfxQueue_Configure(NNSGfdVramTransferTask *pTaskArray, u32 lengthOfArray)
{
    NNSGfdVramTransferTaskQueue *queue = &data_0205a8d0;

    queue->pTaskArray = pTaskArray;
    queue->lengthOfArray = lengthOfArray;
    func_02013f34(&data_0205a8d0_budget);
}