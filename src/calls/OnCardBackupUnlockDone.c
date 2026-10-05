#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void *CARD_LockBackup(int id);
extern void CARD_UnlockBackup(int id);
extern void IncrementBusyCounter(void);
extern void ReadCardBackupSync(int a, void *buf, int b);
extern void DecrementBusyCounterIfPositive(void);

int OnCardBackupUnlockDone(void)
{
    u32 buffer;

    CARD_LockBackup(data_0205fe00.resourceId);
    IncrementBusyCounter();
    ReadCardBackupSync(0, &buffer, 1);
    CARD_UnlockBackup(data_0205fe00.resourceId);
    DecrementBusyCounterIfPositive();
    return 0;
}
