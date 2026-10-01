typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NNSGfdVramTransferTask {
    int type;
    void *pSrc;
    u32 dstAddr;
    u32 szByte;
} NNSGfdVramTransferTask;

typedef struct NNSGfdVramTransferTaskQueue {
    NNSGfdVramTransferTask *pTaskArray;
    u32 lengthOfArray;
    u16 idxFront;
    u16 idxRear;
    u16 numTasks;
    u16 pad16_;
    u32 totalSize;
} NNSGfdVramTransferTaskQueue;

extern NNSGfdVramTransferTask *func_02013f88(NNSGfdVramTransferTaskQueue *queue);
extern int func_02013fa8(NNSGfdVramTransferTaskQueue *queue);
extern void func_02013ef8(NNSGfdVramTransferTask *task, int underBudget);
extern void DC_StoreAll(void);
extern NNSGfdVramTransferTaskQueue data_0205a8d0;
extern NNSGfdVramTransferTaskQueue data_0205a8d0_budget;

void FrameStep_UpdateTaskQueue(void)
{
    NNSGfdVramTransferTaskQueue *queue = &data_0205a8d0;
    NNSGfdVramTransferTask *task;
    u8 underBudget;

    task = func_02013f88(queue);
    underBudget = data_0205a8d0_budget.totalSize < 0x2400;
    if (underBudget == 0) {
        DC_StoreAll();
    }

    if (func_02013fa8(queue) != 0) {
        do {
            func_02013ef8(task, underBudget);
            queue->totalSize -= task->szByte;
            task = func_02013f88(queue);
        } while (func_02013fa8(queue) != 0);
    }
}