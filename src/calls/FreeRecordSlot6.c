#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x34];
    void *slot6;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot 6. */
void FreeRecordSlot6(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slot6);
    manager->slot6 = 0;
}
