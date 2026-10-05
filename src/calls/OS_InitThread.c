#include "nitro/types.h"

typedef struct OSThread OSThread;

struct OSThread {
    u8 context[0x64];
    u32 state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    void *queue;
    OSThread *linkPrev;
    OSThread *linkNext;
    void *mutex;
    void *mutexQueueHead;
    void *mutexQueueTail;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    OSThread *joinQueueHead;
    OSThread *joinQueueTail;
    void *specific[3];
    void *alarmForSleep;
    void *destructor;
    void *userParameter;
    int systemErrno;
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void *switchCallback;
} OSThreadInfo;

typedef struct OSThreadSystem {
    u32 unused_00;
    u32 rescheduleCount;
    OSThread **currentThreadPtr;
    BOOL isThreadInitialized;
    u32 unused_10[2];
    int threadIdCount;
    OSThreadInfo threadInfo;
} OSThreadSystem;

extern OSThreadSystem OSi_ThreadSystemState;
extern OSThread OSi_IdleThread;
extern OSThread data_02056c3c;
extern u32 OSi_IdleThreadStack[50];
extern unsigned char SDK_AUTOLOAD_DTCM_START[];
extern void SDK_SYS_STACKSIZE(void);
extern void SDK_IRQ_STACKSIZE(void);

extern u32 OS_SetSwitchThreadCallback(u32 value);
extern void OS_CreateThread(OSThread *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 priority);
extern void OSi_IdleThreadProc(void *arg);

#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE)
#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE)
#define OSi_LAUNCHER_STACK_LO_DEFAULT 0x027e0280
#define OSi_LAUNCHER_STACK_BOTTOM ((u32)SDK_AUTOLOAD_DTCM_START + 0x3f80 - OSi_IRQ_STACKSIZE)

void OS_InitThread(void)
{
    void *stackLo;

    if (OSi_ThreadSystemState.isThreadInitialized) {
        return;
    }
    OSi_ThreadSystemState.isThreadInitialized = TRUE;

    OSi_ThreadSystemState.currentThreadPtr = &OSi_ThreadSystemState.threadInfo.current;
    data_02056c3c.priority = 16;
    data_02056c3c.id = 0;
    data_02056c3c.state = 1;
    data_02056c3c.next = NULL;
    data_02056c3c.profiler = NULL;

    OSi_ThreadSystemState.threadInfo.list = &data_02056c3c;
    OSi_ThreadSystemState.threadInfo.current = &data_02056c3c;

    stackLo = (OSi_SYS_STACKSIZE <= 0) ?
              (void *)((u32)OSi_LAUNCHER_STACK_LO_DEFAULT - OSi_SYS_STACKSIZE) :
              (void *)(OSi_LAUNCHER_STACK_BOTTOM - OSi_SYS_STACKSIZE);

    data_02056c3c.stackBottom = OSi_LAUNCHER_STACK_BOTTOM;
    data_02056c3c.stackTop = (u32)stackLo;
    data_02056c3c.stackWarningOffset = 0;

    *(u32 *)(data_02056c3c.stackBottom - sizeof(u32) * 2) = 0xFDDB597D;
    *(u32 *)data_02056c3c.stackTop = 0x7BF9DD5B;

    data_02056c3c.joinQueueHead = data_02056c3c.joinQueueTail = NULL;

    OSi_ThreadSystemState.threadInfo.isNeedRescheduling = FALSE;
    OSi_ThreadSystemState.threadInfo.irqDepth = 0;

    *(OSThreadInfo **)0x02ffffa0 = &OSi_ThreadSystemState.threadInfo;

    OS_SetSwitchThreadCallback(0);

    OS_CreateThread(&OSi_IdleThread, OSi_IdleThreadProc, NULL, OSi_IdleThreadStack + 50, sizeof(OSi_IdleThreadStack), 31);

    OSi_IdleThread.priority = 32;
    OSi_IdleThread.state = 1;
}
