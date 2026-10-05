#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    int threadResult;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern BOOL CARDi_RequestStreamCommand(u32 src, u32 dst, u32 length, void *callback, void *arg,
                                                BOOL async, s32 requestType, s32 requestRetry, s32 requestMode);
extern int CARD_GetResultCode(void);

int WriteCardBackupSync(u32 backupOffset, u32 buffer, u32 length)
{
    CARDi_RequestStreamCommand(buffer, backupOffset, length, NULL, NULL, FALSE, 8, 10, 2);
    return data_0205fe00.threadResult = CARD_GetResultCode();
}
