#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
    u8 pad_04[4];
    void *buffer;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void IncrementBusyCounter(void);
extern void *CARD_LockBackup(int id);
extern int ReadCardBackupSync(int a, void *buf, int b);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int WriteCardBackupSync(int offset, void *buffer, u32 length);
extern void CARD_UnlockBackup(int id);
extern void OS_WaitVBlankIntr(void);
extern void DecrementBusyCounterIfPositive(void);

int WriteCardSlotHeaders(int slot)
{
    int scratch;

    IncrementBusyCounter();
    CARD_LockBackup(data_0205fe00.resourceId);
    if (ReadCardBackupSync(0, &scratch, 1) == 0) {
        MI_CpuFill8(data_0205fe00.buffer, 0, 0x3c18);
        slot *= 2;
        if (WriteCardBackupSync(slot * 0x3c18 + 0x20, data_0205fe00.buffer, 0x20) == 0) {
            CARD_UnlockBackup(data_0205fe00.resourceId);
            OS_WaitVBlankIntr();
            CARD_LockBackup(data_0205fe00.resourceId);
            if (WriteCardBackupSync((slot + 1) * 0x3c18 + 0x20, data_0205fe00.buffer, 0x20) == 0) {
                CARD_UnlockBackup(data_0205fe00.resourceId);
                DecrementBusyCounterIfPositive();
                return 1;
            }
        }
    }
    CARD_UnlockBackup(data_0205fe00.resourceId);
    DecrementBusyCounterIfPositive();
    return 0;
}
