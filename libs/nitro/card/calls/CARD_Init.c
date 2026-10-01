typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;
typedef int BOOL;

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
    volatile s32 lockOwner;
    volatile int lockCount;
    OSThreadQueue lockQueue;
    int lockTarget;
    u8 threadContext[0xc0];
    u8 threadStack[0x400];
    void (*taskFunction)(struct CARDiCommon *common);
    void (*callback)(void *argument);
    void *callbackArgument;
    OSThreadQueue busyQueue;
    u32 source;
    u32 destination;
    u32 length;
    u32 dmaChannel;
    const void *dmaInterface;
} CARDiCommon;

#define CARD_STAT_INIT 1
#define CARD_THREAD_PRIORITY_DEFAULT 4
#define MI_DMA_NOT_USE (-1)
#define OS_BOOTTYPE_ROM 1

extern CARDiCommon cardi_common;
typedef struct CARDRomState {
    u32 romBase;
} CARDRomState;
extern CARDRomState sCardRomState;
extern int OS_GetBootType(void);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern void CARDi_InitResourceLock(void);
extern void OS_CreateThread(void *thread, void (*function)(void *), void *argument,
                            void *stackTop, u32 stackSize, u32 priority);
extern void OS_WakeupThreadDirect(void *thread);
extern void CARDi_OldTypeTaskThread(void *argument);
extern void CARDi_InitCommand(void);
extern void CARDi_InitRom(void);
extern void CARD_Enable(BOOL enable);
extern void CARD_InitPulledOutCallback(void);

void CARD_Init(void)
{
    CARDiCommon *common = &cardi_common;

    if (common->flags == 0) {
        common->flags = CARD_STAT_INIT;

        if (OS_GetBootType() == OS_BOOTTYPE_ROM) {
            MI_CpuCopy8((const void *)0x02fffe00, (void *)0x02fffa80, 0x160);
        }

        common->source = 0;
        common->destination = 0;
        common->length = 0;
        common->dmaChannel = MI_DMA_NOT_USE;
        common->dmaInterface = 0;
        common->instructionFlushThreshold = 0x400;
        common->dataFlushThreshold = 0x2400;
        sCardRomState.romBase = 0;
        common->priority = CARD_THREAD_PRIORITY_DEFAULT;

        CARDi_InitResourceLock();

        common->callback = 0;
        common->callbackArgument = 0;
        common->busyQueue.tail = 0;
        common->busyQueue.head = 0;
        OS_CreateThread(common->threadContext, CARDi_OldTypeTaskThread, 0,
                        common->threadStack + sizeof(common->threadStack),
                        sizeof(common->threadStack), common->priority);
        OS_WakeupThreadDirect(common->threadContext);

        CARDi_InitCommand();
        CARDi_InitRom();

        if (OS_GetBootType() == OS_BOOTTYPE_ROM) {
            CARD_Enable(1);
        }

        CARD_InitPulledOutCallback();
    }
}