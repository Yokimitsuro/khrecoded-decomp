typedef unsigned char u8;
typedef unsigned long u32;
typedef int BOOL;
typedef u32 OSIntrMode;
typedef void (*MIDmaCallback)(void *argument);

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct CARDiCommandArg {
    int result;
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *command;
    volatile u32 flags;
    u8 reserved008[0x4e4];
    MIDmaCallback callback;
    void *callbackArgument;
    OSThreadQueue busyQueue;
} CARDiCommon;

#define CARD_STAT_BUSY 4
#define CARD_RESULT_SUCCESS 0

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
extern void OS_SleepThread(OSThreadQueue *queue);

BOOL CARDi_WaitForTask(CARDiCommon *common, BOOL restart,
                       MIDmaCallback callback, void *callbackArgument)
{
    OSIntrMode previousMode = OS_DisableInterrupts();

    while ((common->flags & CARD_STAT_BUSY) != 0) {
        OS_SleepThread(&common->busyQueue);
    }

    if (restart) {
        common->flags |= CARD_STAT_BUSY;
        common->callback = callback;
        common->callbackArgument = callbackArgument;
    }
    (void)OS_RestoreInterrupts(previousMode);
    return common->command->result == CARD_RESULT_SUCCESS;
}