typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

typedef int PXIFifoTag;
typedef struct SNDCommand {
    struct SNDCommand *next;
    u32 id;
    u32 arg[4];
} SNDCommand;
typedef struct SNDSharedWork SNDSharedWork;
#define SND_COMMAND_NUM 256
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1
#define SND_COMMAND_SHARED_WORK 0x1d
#define PXI_FIFO_TAG_SOUND 7
#define PXI_PROC_ARM7 1

typedef struct SNDCommandQueueState {
    SNDCommand *freeList; u32 finishedTag; SNDCommand *reserveList; SNDCommand *reserveListEnd;
    SNDCommand *freeListEnd; int waitingQueueRead; int waitingQueueWrite; int waitingQueueCount;
    u32 currentTag; SNDCommand *waitingQueue[9];
} SNDCommandQueueState;
extern SNDCommandQueueState data_02057c50;
#define sFreeList data_02057c50.freeList
#define sFinishedTag data_02057c50.finishedTag
#define sReserveList data_02057c50.reserveList
#define sReserveListEnd data_02057c50.reserveListEnd
#define sFreeListEnd data_02057c50.freeListEnd
#define sWaitingCommandListQueueRead data_02057c50.waitingQueueRead
#define sWaitingCommandListQueueWrite data_02057c50.waitingQueueWrite
#define sWaitingCommandListCount data_02057c50.waitingQueueCount
#define sCurrentTag data_02057c50.currentTag
#define sWaitingCommandListQueue data_02057c50.waitingQueue
extern SNDSharedWork data_02057ca0;
#define sSharedWork data_02057ca0
extern SNDCommand data_02057f20[SND_COMMAND_NUM] __attribute__((aligned(32)));
#define sCommandArray data_02057f20
extern SNDSharedWork *SNDi_SharedWork;
#define SNDi_SharedWork SNDi_SharedWork

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_0200386c(u32 cycles);
#define OS_SpinWait func_0200386c
extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err);
extern BOOL IsCommandAvailable(void);
extern void InitPXI(void);
extern void SNDi_InitSharedWork(SNDSharedWork *work);
extern u32 SNDi_GetFinishedCommandTag(void);
extern SNDCommand *SND_AllocCommand(u32 flags);
extern void func_0200f05c(SNDCommand *command);
#define SND_PushCommand func_0200f05c
extern BOOL SND_FlushCommand(u32 flags);
#define SND_FlushCommand SND_FlushCommand

void SND_CommandInit (void)
{
    SNDCommand * command;
    int i;

    InitPXI();

    sFreeList = &sCommandArray[0];
    for (i = 0; i < SND_COMMAND_NUM - 1; i++) {
        sCommandArray[i].next = &sCommandArray[i + 1];
    }
    sCommandArray[SND_COMMAND_NUM - 1].next = NULL;
    sFreeListEnd = &sCommandArray[SND_COMMAND_NUM - 1];

    sReserveList = NULL;
    sReserveListEnd = NULL;

    sWaitingCommandListCount = 0;

    sWaitingCommandListQueueRead = 0;
    sWaitingCommandListQueueWrite = 0;

    sCurrentTag = 1;
    sFinishedTag = 0;

    SNDi_SharedWork = &sSharedWork;
    SNDi_InitSharedWork(SNDi_SharedWork);

    command = SND_AllocCommand(SND_COMMAND_BLOCK);
    if (command != NULL) {
        command->id = SND_COMMAND_SHARED_WORK;
        command->arg[0] = (u32)SNDi_SharedWork;

        SND_PushCommand(command);
        (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    }

}
