#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    void *slot8;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot 8. */
void FreeRecordSlot8(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slot8);
    manager->slot8 = 0;
}
