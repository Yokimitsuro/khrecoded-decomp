typedef unsigned long u32;
typedef int BOOL;
typedef u32 OSIntrMode;

typedef struct SNDCommand {
    struct SNDCommand *next;
    u32 id;
    u32 arguments[4];
} SNDCommand;

typedef struct SNDCommandState {
    SNDCommand *freeList;
    u32 finishedTag;
    SNDCommand *reserveList;
    SNDCommand *reserveListEnd;
    SNDCommand *freeListEnd;
    int waitingQueueRead;
    int waitingQueueWrite;
    int waitingListCount;
    u32 currentTag;
} SNDCommandState;

#define SND_COMMAND_NUM 256
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1
#define SND_COMMAND_IMMEDIATE 2
#define PXI_FIFO_TAG_SOUND 7

extern SNDCommandState data_02057c50;
extern SNDCommand *data_02057c74[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];
extern SNDCommand data_02057f20[SND_COMMAND_NUM];
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void DC_FlushRange(void *address, u32 size);
extern const SNDCommand *SND_RecvCommandReply(u32 flags);
extern int PXI_SendWordByFifo(int tag, u32 data, int error);
extern void RequestCommandProc(void);

BOOL SND_FlushCommand(u32 flags)
{
    OSIntrMode interruptState = OS_DisableInterrupts();

    if (!data_02057c50.reserveList) {
        (void)OS_RestoreInterrupts(interruptState);
        return 1;
    }

    if (data_02057c50.waitingListCount >= SND_PXI_FIFO_MESSAGE_BUFSIZE) {
        if (!(flags & SND_COMMAND_BLOCK)) {
            (void)OS_RestoreInterrupts(interruptState);
            return 0;
        }

        do {
            (void)SND_RecvCommandReply(SND_COMMAND_BLOCK);
        } while (data_02057c50.waitingListCount >=
                 SND_PXI_FIFO_MESSAGE_BUFSIZE);

        if (!data_02057c50.reserveList) {
            (void)OS_RestoreInterrupts(interruptState);
            return 1;
        }
    }

    DC_FlushRange(data_02057f20, sizeof(data_02057f20));
    if (PXI_SendWordByFifo(PXI_FIFO_TAG_SOUND,
                           (u32)data_02057c50.reserveList, 0) < 0) {
        if (!(flags & SND_COMMAND_BLOCK)) {
            (void)OS_RestoreInterrupts(interruptState);
            return 0;
        }

        while (data_02057c50.waitingListCount >=
                   SND_PXI_FIFO_MESSAGE_BUFSIZE ||
               PXI_SendWordByFifo(PXI_FIFO_TAG_SOUND,
                                  (u32)data_02057c50.reserveList, 0) < 0) {
            (void)OS_RestoreInterrupts(interruptState);
            (void)SND_RecvCommandReply(SND_COMMAND_NOBLOCK);
            interruptState = OS_DisableInterrupts();

            DC_FlushRange(data_02057f20, sizeof(data_02057f20));
            if (!data_02057c50.reserveList) {
                (void)OS_RestoreInterrupts(interruptState);
                return 1;
            }
        }
    }

    data_02057c74[data_02057c50.waitingQueueWrite] =
        data_02057c50.reserveList;
    data_02057c50.waitingQueueWrite++;
    if (data_02057c50.waitingQueueWrite > SND_PXI_FIFO_MESSAGE_BUFSIZE) {
        data_02057c50.waitingQueueWrite = 0;
    }

    data_02057c50.reserveList = 0;
    data_02057c50.reserveListEnd = 0;
    data_02057c50.waitingListCount++;
    data_02057c50.currentTag++;

    (void)OS_RestoreInterrupts(interruptState);
    if (flags & SND_COMMAND_IMMEDIATE) {
        RequestCommandProc();
    }

    return 1;
}