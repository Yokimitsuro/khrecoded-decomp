#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x70];
    void *tableE;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record table E. */
void ReleaseRecordTableE(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->tableE);
    manager->tableE = 0;
}
