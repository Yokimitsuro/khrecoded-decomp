#include "nitro/types.h"

typedef struct {
    u8 blockCounter;
    u8 slot;
    u8 pad_02[6];
    void *buffer;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void IncrementBusyCounter(void);
extern void StartCardTransferThread(void *src, void *dst, u32 length);

void StartCardWriteFromSlot(u8 slot)
{
    IncrementBusyCounter();
    data_0205fe00.blockCounter = 0;
    data_0205fe00.slot = slot;
    StartCardTransferThread(
        (void *)((data_0205fe00.slot << 1) * 0x3c18 + 0x20),
        data_0205fe00.buffer, 0x3c18);
}
