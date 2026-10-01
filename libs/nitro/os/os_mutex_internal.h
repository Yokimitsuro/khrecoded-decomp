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
    u32 count;
    OSMutexLink link;
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void *switchCallback;
} OSThreadInfo;

enum {
    OS_THREAD_STATE_WAITING = 0,
    OS_MUTEX_COUNT_MASK = 0x00ffffff,
    OS_MUTEX_TYPE_MASK = 0xff000000,
    OS_MUTEX_TYPE_NONE = 0,
    OS_MUTEX_TYPE_NORMAL = 0x10000000
};

static inline void OSi_SetMutexCount(OSMutex *mutex, s32 count)
{
    mutex->count = (mutex->count & OS_MUTEX_TYPE_MASK) | ((u32)count & OS_MUTEX_COUNT_MASK);
}

static inline u32 OSi_GetMutexType(const OSMutex *mutex)
{
    return mutex->count & OS_MUTEX_TYPE_MASK;
}

static inline void OSi_SetMutexType(OSMutex *mutex, u32 type)
{
    mutex->count = type | (mutex->count & OS_MUTEX_COUNT_MASK);
}

#endif
