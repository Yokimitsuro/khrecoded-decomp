#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *slotPair2;
    void *slotPair2Aux;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot pair 2. */
void FreeRecordSlotPair2(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slotPair2);
    NNSi_FndFreeFromDefaultHeap(manager->slotPair2Aux);
    manager->slotPair2 = 0;
    manager->slotPair2Aux = 0;
}
