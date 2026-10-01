typedef unsigned char u8;
typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDiCommandArg {
    int result;
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *command;
    volatile u32 flags;
    u32 priority;
    u8 reserved00c[0x1c];
    u8 threadContext[0xc0];
    u8 threadStack[0x400];
    void (*taskFunction)(struct CARDiCommon *common);
} CARDiCommon;

#define CARD_STAT_TASK 8

extern CARDiCommon cardi_common;
extern BOOL OS_SetThreadPriority(void *thread, u32 priority);
extern void OS_WakeupThreadDirect(void *thread);
extern void CARDi_EndTask(CARDiCommon *common);

BOOL CARDi_ExecuteOldTypeTask(void (*task)(CARDiCommon *common), BOOL asynchronous)
{
    CARDiCommon *common = &cardi_common;

    if (asynchronous) {
        (void)OS_SetThreadPriority(common->threadContext, common->priority);
        common->taskFunction = task;
        common->flags |= CARD_STAT_TASK;
        OS_WakeupThreadDirect(common->threadContext);
    } else {
        task(common);
        CARDi_EndTask(common);
    }

    return asynchronous ? 1 : common->command->result == 0;
}