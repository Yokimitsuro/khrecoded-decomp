typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;
typedef int OSIntrMode;

typedef struct OSThread OSThread;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSMutex OSMutex;

typedef struct OSThreadLink {
    OSThread *prev;
    OSThread *next;
} OSThreadLink;

typedef struct OSMutexQueue {
    OSMutex *head;
    OSMutex *tail;
} OSMutexQueue;

struct OSThread {
    unsigned char context[0x64];
    int state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    OSThreadQueue *queue;
    OSThreadLink link;
    OSMutex *mutex;
    OSMutexQueue mutexQueue;
};

typedef struct OSThreadSystemState {
    unsigned char reserved000[0x24];
    OSThread *list;
} OSThreadSystemState;

extern OSThreadSystemState OSi_ThreadSystemState;
extern OSThread OSi_IdleThread;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
extern void OSi_InsertThreadToList(OSThread *thread);
extern void OSi_RescheduleThread(void);

BOOL OS_SetThreadPriority(OSThread *thread, u32 priority)
{
    OSThread *current = OSi_ThreadSystemState.list;
    OSThread *previous = 0;
    OSIntrMode interruptMode;

    interruptMode = OS_DisableInterrupts();

    while (current && current != thread) {
        previous = current;
        current = current->next;
    }

    if (!current || current == &OSi_IdleThread) {
        (void)OS_RestoreInterrupts(interruptMode);
        return 0;
    }

    if (current->priority != priority) {
        if (!previous) {
            OSi_ThreadSystemState.list = thread->next;
        } else {
            previous->next = thread->next;
        }

        thread->priority = priority;
        OSi_InsertThreadToList(thread);
        OSi_RescheduleThread();
    }

    (void)OS_RestoreInterrupts(interruptMode);
    return 1;
}