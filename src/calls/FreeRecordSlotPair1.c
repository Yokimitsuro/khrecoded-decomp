#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void *slotPair1;
    void *slotPair1Aux;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot pair 1. */
void FreeRecordSlotPair1(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slotPair1);
    NNSi_FndFreeFromDefaultHeap(manager->slotPair1Aux);
    manager->slotPair1 = 0;
    manager->slotPair1Aux = 0;
}
