#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x08];
    void *slotPair0;
    void *slotPair0Aux;
} RecordManager;

extern RecordManager *gRecordManager;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot pair 0. */
void FreeRecordSlotPair0(void)
{
    RecordManager *manager = gRecordManager;

    NNSi_FndFreeFromDefaultHeap(manager->slotPair0);
    NNSi_FndFreeFromDefaultHeap(manager->slotPair0Aux);
    manager->slotPair0 = 0;
    manager->slotPair0Aux = 0;
}
