#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    void *slot5;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot 5. */
void FreeRecordSlot5(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slot5);
    manager->slot5 = 0;
}
