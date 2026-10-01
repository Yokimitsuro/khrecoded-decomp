typedef unsigned long u32;
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

#define SND_COMMAND_BLOCK 1
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8

extern SNDCommandState data_02057c50;
extern SNDCommand *data_02057c74[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SpinWait(u32 cycles);
extern u32 SNDi_GetFinishedCommandTag(void);

const SNDCommand *SND_RecvCommandReply(u32 flags)
{
    OSIntrMode interruptState = OS_DisableInterrupts();
    SNDCommand *commandList;
    SNDCommand *commandListEnd;

    if (flags & SND_COMMAND_BLOCK) {
        while (data_02057c50.finishedTag == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(interruptState);
            OS_SpinWait(50);
            interruptState = OS_DisableInterrupts();
        }
    } else {
        if (data_02057c50.finishedTag == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(interruptState);
            return 0;
        }
    }

    commandList = data_02057c74[data_02057c50.waitingQueueRead];
    data_02057c50.waitingQueueRead++;
    if (data_02057c50.waitingQueueRead > SND_PXI_FIFO_MESSAGE_BUFSIZE) {
        data_02057c50.waitingQueueRead = 0;
    }

    commandListEnd = commandList;
    while (commandListEnd->next) {
        commandListEnd = commandListEnd->next;
    }

    if (data_02057c50.freeListEnd) {
        data_02057c50.freeListEnd->next = commandList;
    } else {
        data_02057c50.freeList = commandList;
    }
    data_02057c50.freeListEnd = commandListEnd;

    data_02057c50.waitingListCount--;
    data_02057c50.finishedTag++;

    (void)OS_RestoreInterrupts(interruptState);
    return commandList;
}