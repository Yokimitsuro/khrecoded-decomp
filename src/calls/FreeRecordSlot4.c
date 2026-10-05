#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    void *slot4;
} RecordManager;

extern RecordManager *gRecordManager;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot 4. */
void FreeRecordSlot4(void)
{
    RecordManager *manager = gRecordManager;

    NNSi_FndFreeFromDefaultHeap(manager->slot4);
    manager->slot4 = 0;
}
