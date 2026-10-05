#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    void *slotPair3;
    void *slotPair3Aux;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record slot pair 3. */
void FreeRecordSlotPair3(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->slotPair3);
    NNSi_FndFreeFromDefaultHeap(manager->slotPair3Aux);
    manager->slotPair3 = 0;
    manager->slotPair3Aux = 0;
}
