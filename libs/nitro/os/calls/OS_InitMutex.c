typedef unsigned int u32;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct OSMutex {
    OSThreadQueue queue;
    void *thread;
    int count;
} OSMutex;

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = 0;
}

static inline void OS_SetMutexCount(OSMutex *mutex, int count)
{
    mutex->count = (int)(((u32)mutex->count & 0xff000000) | ((u32)count & 0x00ffffff));
}

static inline void OS_SetMutexType(OSMutex *mutex, u32 type)
{
    mutex->count = (int)(type | ((u32)mutex->count & 0x00ffffff));
}

void OS_InitMutex(OSMutex *mutex)
{
    OS_InitThreadQueue(&mutex->queue);
    mutex->thread = 0;
    OS_SetMutexCount(mutex, 0);
    OS_SetMutexType(mutex, 0);
}