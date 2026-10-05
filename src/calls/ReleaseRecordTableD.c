#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x64];
    void *tableD;
    void *tableDAux1;
    void *tableDAux2;
} RecordManager;

extern RecordManager *data_020613d0;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record table D. */
void ReleaseRecordTableD(void)
{
    RecordManager *manager = data_020613d0;

    NNSi_FndFreeFromDefaultHeap(manager->tableD);
    NNSi_FndFreeFromDefaultHeap(manager->tableDAux1);
    NNSi_FndFreeFromDefaultHeap(manager->tableDAux2);
    manager->tableD = 0;
    manager->tableDAux1 = 0;
    manager->tableDAux2 = 0;
}
