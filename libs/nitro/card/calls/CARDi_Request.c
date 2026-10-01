#include "libs/nitro/card/card_rom_internal.h"

typedef struct OSThread OSThread;
typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void *switchCallback;
} OSThreadInfo;

extern OSThreadInfo OSi_ThreadInfo;
extern BOOL PXI_IsCallbackReady(int tag, int processor);
extern void OS_SpinWait(u32 cycles);
extern void DC_FlushRange(const void *address, u32 length);
extern void DC_WaitWriteBufferEmpty(void);
extern int PXI_SendWordByFifo(int tag, u32 data, BOOL error);
extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_SleepThread(OSThreadQueue *queue);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
extern void DC_InvalidateRange(void *address, u32 length);

#define CARD_STAT_INIT_CMD 2
#define CARD_STAT_WAITFOR7ACK 0x20
#define CARD_REQ_INIT 0
#define CARD_RESULT_SUCCESS 0
#define CARD_RESULT_TIMEOUT 4
#define PXI_FIFO_TAG_FS 11
#define PXI_PROC_ARM7 1

static inline void CARDi_SendPxi(u32 data)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_FS, data, 1) < 0) {
    }
}

BOOL CARDi_Request(CARDiCommon *common, int requestType, int retryCount)
{
    if ((common->flags & CARD_STAT_INIT_CMD) == 0) {
        common->flags |= CARD_STAT_INIT_CMD;
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_FS, PXI_PROC_ARM7)) {
            OS_SpinWait(50);
        }

        (void)CARDi_Request(common, CARD_REQ_INIT, 1);
    }

    DC_FlushRange(common->command, sizeof(*common->command));
    DC_WaitWriteBufferEmpty();

    common->currentArm9Thread = OSi_ThreadInfo.current;

    do {
        common->flags |= CARD_STAT_WAITFOR7ACK;
        CARDi_SendPxi((u32)requestType);

        switch (requestType) {
        case CARD_REQ_INIT:
            CARDi_SendPxi((u32)common->command);
            break;
        }

        {
            OSIntrMode interrupts = OS_DisableInterrupts();
            while ((common->flags & CARD_STAT_WAITFOR7ACK) != 0) {
                OS_SleepThread(0);
            }
            (void)OS_RestoreInterrupts(interrupts);
        }

        DC_InvalidateRange(common->command, sizeof(*common->command));
    } while (common->command->result == CARD_RESULT_TIMEOUT && --retryCount > 0);

    return common->command->result == CARD_RESULT_SUCCESS;
}
