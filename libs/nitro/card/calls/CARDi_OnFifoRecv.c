typedef unsigned char u8;
typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDiCommon {
    void *command;
    volatile u32 flags;
    u8 reserved008[0x514];
    void *currentThread;
} CARDiCommon;

#define CARD_STAT_WAITFOR7ACK 0x20
#define PXI_FIFO_TAG_FS 11

extern CARDiCommon cardi_common;
extern void OS_WakeupThreadDirect(void *thread);

void CARDi_OnFifoRecv(int tag, u32 data, BOOL error)
{
    (void)data;

    if (tag == PXI_FIFO_TAG_FS && error) {
        CARDiCommon *common = &cardi_common;
        common->flags &= ~CARD_STAT_WAITFOR7ACK;
        OS_WakeupThreadDirect(common->currentThread);
    }
}