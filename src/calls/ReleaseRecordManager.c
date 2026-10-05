#include "nitro/types.h"

typedef struct RecordManager {
    void *containerA;
    void *containerB;
    u8 pad_08[0x3c];
    u8 refCounts[14];
    u8 useCount;
    u8 pad_53[0x74 - 0x53];
} RecordManager;

extern RecordManager *gRecordManager;
extern BOOL ReleaseRecordSlot(s32 slot);
extern void ZeroHalfThenFree(void *container);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseRecordManager(void)
{
    RecordManager *manager = gRecordManager;
    int slot;

    if (manager == NULL) {
        return;
    }
    manager->useCount--;
    if (manager->useCount != 0) {
        return;
    }
    for (slot = 0; slot < 14; slot++) {
        if (manager->refCounts[slot] != 0) {
            manager->refCounts[slot] = 1;
            ReleaseRecordSlot(slot);
        }
    }
    ZeroHalfThenFree(manager->containerB);
    ZeroHalfThenFree(manager->containerA);
    NNSi_FndFreeFromDefaultHeap(manager);
    gRecordManager = NULL;
}
