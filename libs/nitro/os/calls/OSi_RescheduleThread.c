typedef int BOOL;
typedef struct OSContext { char data[1]; } OSContext;
typedef void (*OSSwitchThreadCallback)(void *from, void *to);
extern BOOL OS_SaveContext(OSContext *context);
extern void OS_LoadContext(OSContext *context);
extern int OS_GetProcMode(void);
extern void *func_02002b9c(void);
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
extern OSThreadSystem data_02056b50;
extern OSThreadInfo OSi_ThreadInfo;

void OSi_RescheduleThread(void)
{
    OSThreadInfo *info;
    void **currentThreadPtr;
    void *current;
    void *next;
    OSSwitchThreadCallback callback;

    if (data_02056b50.rescheduleCount != 0)
        return;

    info = &OSi_ThreadInfo;
    if (data_02056b50.threadInfo.irqDepth != 0 || OS_GetProcMode() == 0x12) {
        info->isNeedRescheduling = 1;
        return;
    }

    currentThreadPtr = (void **)data_02056b50.currentThreadPtr;
    current = *currentThreadPtr;
    next = func_02002b9c();

    if (current == next || next == 0)
        return;

    if (*(int *)((char *)current + 0x64) != 2) {
        if (OS_SaveContext((OSContext *)current))
            return;
    }

    callback = data_02056b50.systemCallback;
    if (callback != 0)
        callback(current, next);

    callback = info->switchCallback;
    if (callback != 0)
        callback(current, next);

    data_02056b50.threadInfo.currentThread = next;
    OS_LoadContext((OSContext *)next);
}