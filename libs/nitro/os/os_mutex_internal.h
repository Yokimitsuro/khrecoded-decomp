#ifndef NITRO_OS_MUTEX_INTERNAL_H
#define NITRO_OS_MUTEX_INTERNAL_H

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef int OSIntrMode;

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct OSThreadLink {
    OSThread *prev;
    OSThread *next;
} OSThreadLink;

typedef struct OSMutexQueue {
    OSMutex *head;
    OSMutex *tail;
} OSMutexQueue;

typedef struct OSMutexLink {
    OSMutex *next;
    OSMutex *prev;
} OSMutexLink;

struct OSThread {
    unsigned char context[0x64];
    s32 state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    OSThreadQueue *queue;
    OSThreadLink link;
    OSMutex *mutex;
    OSMutexQueue mutexQueue;
};

struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void *switchCallback;
} OSThreadInfo;

extern OSThreadInfo OSi_ThreadInfo;

static inline OSThreadInfo *OS_GetThreadInfo(void)
{
    return &OSi_ThreadInfo;
}

static inline OSThread *OS_GetCurrentThread(void)
{
    return OS_GetThreadInfo()->current;
}

enum {
    OS_THREAD_STATE_WAITING = 0,
    OSi_MUTEX_COUNT_MASK = 0x00ffffff,
    OSi_MUTEX_TYPE_MASK = 0xff000000,
    OS_MUTEX_TYPE_NONE = 0,
    OS_MUTEX_TYPE_STD = 0x10000000,
    OS_MUTEX_TYPE_R = 0x20000000,
    OS_MUTEX_TYPE_W = 0x30000000
};

static inline void OS_SetMutexCount(OSMutex *mutex, s32 count)
{
    mutex->count = (s32)(((u32)mutex->count & OSi_MUTEX_TYPE_MASK) |
                         ((u32)count & OSi_MUTEX_COUNT_MASK));
}

static inline s32 OS_GetMutexCount(OSMutex *mutex)
{
    return (s32)((u32)mutex->count & OSi_MUTEX_COUNT_MASK);
}

static inline void OS_IncreaseMutexCount(OSMutex *mutex)
{
    u32 type = (u32)mutex->count & OSi_MUTEX_TYPE_MASK;

    mutex->count++;
    mutex->count = (s32)(type | ((u32)mutex->count & OSi_MUTEX_COUNT_MASK));
}

static inline void OS_DecreaseMutexCount(OSMutex *mutex)
{
    u32 type = (u32)mutex->count & OSi_MUTEX_TYPE_MASK;

    mutex->count--;
    mutex->count = (s32)(type | ((u32)mutex->count & OSi_MUTEX_COUNT_MASK));
}

static inline void OS_SetMutexType(OSMutex *mutex, u32 type)
{
    mutex->count = (s32)(type | ((u32)mutex->count & OSi_MUTEX_COUNT_MASK));
}

static inline u32 OS_GetMutexType(OSMutex *mutex)
{
    return (u32)mutex->count & OSi_MUTEX_TYPE_MASK;
}

#endif
