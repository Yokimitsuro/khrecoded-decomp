#include "nitro/types.h"

typedef struct {
    u8 blockCounter;
    u8 slot;
    u16 resourceId;
    u8 pad_04[4];
    void *buffer;
    u8 pad_0c[8];
    int threadResult;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void *PXI_Init_02026ca8(void);
extern int CARD_GetResultCode(void);
extern void CARD_UnlockBackup(int resource);
extern void DecrementBusyCounterIfPositive(void);
extern void EmitCommandVariantA(int offset, void *buffer, int length);

int PollCardThreadState(void)
{
    int combinedIndex;

    if (PXI_Init_02026ca8() != 0) {
        data_0205fe00.threadResult = CARD_GetResultCode();
        if (data_0205fe00.threadResult != 0) {
            CARD_UnlockBackup(data_0205fe00.resourceId);
            DecrementBusyCounterIfPositive();
            return 3;
        }
        data_0205fe00.blockCounter = data_0205fe00.blockCounter + 1;
        if (data_0205fe00.blockCounter >= 2) {
            CARD_UnlockBackup(data_0205fe00.resourceId);
            DecrementBusyCounterIfPositive();
            return 0;
        }
        combinedIndex = data_0205fe00.blockCounter + data_0205fe00.slot * 2;
        EmitCommandVariantA(combinedIndex * 0x3c18 + 0x20, data_0205fe00.buffer, 0x3c18);
    }
    return 1;
}
