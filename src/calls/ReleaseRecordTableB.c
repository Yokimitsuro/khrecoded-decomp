#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    void *tableB;
    void *tableBAux;
} RecordManager;

extern RecordManager *gRecordManager;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record table B. */
void ReleaseRecordTableB(void)
{
    RecordManager *manager = gRecordManager;

    NNSi_FndFreeFromDefaultHeap(manager->tableB);
    NNSi_FndFreeFromDefaultHeap(manager->tableBAux);
    manager->tableB = 0;
    manager->tableBAux = 0;
}
