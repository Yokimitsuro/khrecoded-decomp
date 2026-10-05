#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x38];
    void *slot7;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot 7. */
void FreeRecordSlot7(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slot7);
    manager->slot7 = 0;
}
