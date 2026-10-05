#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x2c0];
    u32 src;
    s32 length;
    u32 dst;
    int result;
} CardThreadBlock;

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
    u8 pad_04[0x10];
    int threadResult;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void *CARD_LockBackup(int id);
extern void CARD_UnlockBackup(int id);
extern BOOL CARDi_RequestStreamCommand(u32 src, u32 dst, u32 length, void *callback, void *arg,
                                                BOOL async, s32 requestType, s32 requestRetry, s32 requestMode);
extern int CARD_GetResultCode(void);
extern void OS_RescheduleThread(void);

void CardTransferThreadMain(CardThreadBlock *block)
{
    u32 src = block->src;
    s32 remaining = block->length;
    u32 dst = block->dst;
    s32 chunk;

    do {
        chunk = 0x80;
        if (remaining <= 0x80) {
            chunk = remaining;
        }
        CARD_LockBackup(data_0205fe00.resourceId);
        if (CARDi_RequestStreamCommand(src, dst, chunk, NULL, NULL, FALSE, 6, 1, 0) == 0) {
            block->result = data_0205fe00.threadResult = CARD_GetResultCode();
            CARD_UnlockBackup(data_0205fe00.resourceId);
            return;
        }
        CARD_UnlockBackup(data_0205fe00.resourceId);
        src += chunk;
        dst += chunk;
        remaining -= chunk;
        OS_RescheduleThread();
    } while (remaining > 0);
    block->result = 0;
}
