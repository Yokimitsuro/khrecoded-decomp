typedef unsigned char u8;
typedef unsigned long u32;
typedef u32 OSIntrMode;
typedef int BOOL;

typedef struct CARDiCommon {
    void *command;
    volatile u32 flags;
    u8 reserved008[0x4e0];
    void (*taskFunction)(struct CARDiCommon *common);
} CARDiCommon;

#define CARD_STAT_TASK 8

extern CARDiCommon cardi_common;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(void *queue);
extern BOOL CARDi_ExecuteOldTypeTask(void (*task)(CARDiCommon *common), BOOL asynchronous);

void CARDi_OldTypeTaskThread(void *argument)
{
    CARDiCommon *common = &cardi_common;
    (void)argument;

    for (;;) {
        OSIntrMode state = OS_DisableInterrupts();

        for (;;) {
            if ((common->flags & CARD_STAT_TASK) != 0) {
                break;
            }
            OS_SleepThread(0);
        }

        (void)OS_RestoreInterrupts(state);
        (void)CARDi_ExecuteOldTypeTask(common->taskFunction, 0);
    }
}