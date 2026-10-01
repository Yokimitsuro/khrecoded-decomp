typedef unsigned char u8;
typedef unsigned long u32;
typedef u32 OSIntrMode;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct CARDiCommon {
    void *command;
    volatile u32 flags;
    u8 reserved008[0x4e4];
    void (*callback)(void *argument);
    void *callbackArgument;
    OSThreadQueue busyQueue;
} CARDiCommon;

#define CARD_STAT_BUSY 4
#define CARD_STAT_TASK 8
#define CARD_STAT_CANCEL 0x40

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_WakeupThread(OSThreadQueue *queue);

void CARDi_EndTask(CARDiCommon *common)
{
    void (*callback)(void *) = common->callback;
    void *argument = common->callbackArgument;
    OSIntrMode state = OS_DisableInterrupts();

    common->flags &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
    OS_WakeupThread(&common->busyQueue);
    (void)OS_RestoreInterrupts(state);

    if (callback != 0) {
        callback(argument);
    }
}