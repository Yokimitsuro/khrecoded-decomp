#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    void *tableA;
} RecordManager;

extern RecordManager *gRecordManager;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees and clears record table A. */
void ReleaseRecordTableA(void)
{
    RecordManager *manager = gRecordManager;

    NNSi_FndFreeFromDefaultHeap(manager->tableA);
    manager->tableA = 0;
}
