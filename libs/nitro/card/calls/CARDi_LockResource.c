typedef unsigned long u32;
typedef signed long s32;
typedef u32 OSIntrMode;
typedef s32 CARDiOwner;

typedef enum CARDTargetMode {
    CARD_TARGET_NONE,
    CARD_TARGET_ROM,
    CARD_TARGET_BACKUP,
    CARD_TARGET_RW
} CARDTargetMode;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct CARDiCommon {
    void *command;
    volatile u32 flags;
    u32 priority;
    u32 instructionFlushThreshold;
    u32 dataFlushThreshold;
    volatile CARDiOwner lockOwner;
    volatile int lockCount;
    OSThreadQueue lockQueue[1];
    CARDTargetMode lockTarget;
} CARDiCommon;

#define OS_LOCK_ID_ERROR (-3)

extern CARDiCommon cardi_common;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(OSThreadQueue *queue);
extern void OS_Terminate(void);

void CARDi_LockResource(CARDiOwner owner, CARDTargetMode target)
{
    OSThreadQueue *queue;
    CARDiCommon *const common = &cardi_common;
    OSIntrMode interruptState = OS_DisableInterrupts();

    if (common->lockOwner == owner) {
        if (common->lockTarget != target) {
            OS_Terminate();
        }
    } else {
        queue = common->lockQueue;
        goto checkOwner;
waitForOwner:
        OS_SleepThread(queue);
checkOwner:
        if (common->lockOwner != OS_LOCK_ID_ERROR) {
            goto waitForOwner;
        }
        common->lockOwner = owner;
        common->lockTarget = target;
    }

    ++common->lockCount;
    (void)OS_RestoreInterrupts(interruptState);
}