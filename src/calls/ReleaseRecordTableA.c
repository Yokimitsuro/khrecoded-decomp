#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    void *tableA;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record table A. */
void ReleaseRecordTableA(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->tableA);
    manager->tableA = 0;
}
