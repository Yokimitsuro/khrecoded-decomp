typedef int BOOL;
typedef struct OSContext { char data[1]; } OSContext;
typedef void (*OSSwitchThreadCallback)(void *from, void *to);
extern BOOL OS_SaveContext(OSContext *context);
extern void OS_LoadContext(OSContext *context);
extern int OS_GetProcMode(void);
extern void *OS_SelectThread(void);
typedef struct OSThreadInfo {
    unsigned short isNeedRescheduling;
    unsigned short irqDepth;
    void *currentThread;
    void *list;
    OSSwitchThreadCallback switchCallback;
} OSThreadInfo;
typedef struct OSThreadSystem {
    OSSwitchThreadCallback systemCallback;
    unsigned long rescheduleCount;
    void ***currentThreadPtr;
    char reserved0c[0x10];
    OSThreadInfo threadInfo;
} OSThreadSystem;
extern OSThreadSystem OSi_ThreadSystemState;
extern OSThreadInfo OSi_ThreadInfo;

void OSi_RescheduleThread(void)
{
    OSThreadInfo *info;
    void **currentThreadPtr;
    void *current;
    void *next;
    OSSwitchThreadCallback callback;

    if (OSi_ThreadSystemState.rescheduleCount != 0)
        return;

    info = &OSi_ThreadInfo;
    if (OSi_ThreadSystemState.threadInfo.irqDepth != 0 || OS_GetProcMode() == 0x12) {
        info->isNeedRescheduling = 1;
        return;
    }

    currentThreadPtr = (void **)OSi_ThreadSystemState.currentThreadPtr;
    current = *currentThreadPtr;
    next = OS_SelectThread();

    if (current == next || next == 0)
        return;

    if (*(int *)((char *)current + 0x64) != 2) {
        if (OS_SaveContext((OSContext *)current))
            return;
    }

    callback = OSi_ThreadSystemState.systemCallback;
    if (callback != 0)
        callback(current, next);

    callback = info->switchCallback;
    if (callback != 0)
        callback(current, next);

    OSi_ThreadSystemState.threadInfo.currentThread = next;
    OS_LoadContext((OSContext *)next);
}