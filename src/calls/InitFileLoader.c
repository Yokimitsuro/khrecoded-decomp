#include "nitro/types.h"

typedef struct LoaderRequest {
    struct LoaderRequest *next;
    u8 pad_04[0x30 - 4];
} LoaderRequest;

typedef struct FileLoader {
    void *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
    u8 pad_14[0x18 - 0x14];
    LoaderRequest *freeList;
    LoaderRequest *pool;
} FileLoader;

extern FileLoader gFileLoader;

extern struct {
    void **heap;
    void **defaultHeap;
} data_02060394;

extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void **heap);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void FS_InitFile(void *file);
extern void EnqueueGfxCmd0(void);
extern void EnqueueGfxCmd1(void);
extern void OS_InitMessageQueue(void *queue, void *msgArray, int count);
extern u8 data_02060584;
extern void *data_02060664[0x40];
extern void OS_CreateThread(void *thread, void (*entry)(void *), void *arg, void *stack, u32 stackSize,
                          u32 priority);
extern void OS_WakeupThreadDirect(char *thread);
extern void FileLoader_ThreadMain(void *arg);
extern u8 data_020605a4[];
extern u8 data_020569c8[];

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->tail = 0;
    queue->head = 0;
}

BOOL InitFileLoader(void)
{
    int i;

    if (gFileLoader.work == 0) {
        gFileLoader.work = NNSi_FndAllocFromExpHeapEx(0x23c0, data_02060394.heap);
        MI_CpuFill8(gFileLoader.work, 0, 0x23c0);
        gFileLoader.reader = AllocFromHeapOrDefaultEx(0x420, 0x20, data_02060394.heap);
        gFileLoader.reader2 = AllocFromHeapOrDefaultEx(0x460, 0x20, data_02060394.heap);
        FS_InitFile((u8 *)gFileLoader.reader2 + 0x400);
        gFileLoader.pool = NNSi_FndAllocFromExpHeapEx(0xc00, data_02060394.heap);

        for (i = 0; i < 0x40; i++) {
            gFileLoader.pool[i].next = (i < 0x3f) ? &gFileLoader.pool[i + 1] : 0;
        }

        gFileLoader.freeList = gFileLoader.pool;
        gFileLoader.hookA = EnqueueGfxCmd0;
        gFileLoader.hookB = EnqueueGfxCmd1;
        OS_InitMessageQueue(&data_02060584, data_02060664, 0x40);

        OS_InitThreadQueue((OSThreadQueue *)((u8 *)gFileLoader.reader2 + 0x44c));

        OS_CreateThread(data_020605a4, FileLoader_ThreadMain, 0, data_020569c8, 0x800, 0x11);
        OS_WakeupThreadDirect((char *)data_020605a4);
    }
    return 1;
}
