#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5c];
    void *tableC;
    void *tableCAux;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record table C. */
void ReleaseRecordTableC(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->tableC);
    NNSi_FndFreeFromDefaultHeap(manager->tableCAux);
    manager->tableC = 0;
    manager->tableCAux = 0;
}
