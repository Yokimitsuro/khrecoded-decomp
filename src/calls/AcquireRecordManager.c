#include "nitro/types.h"

typedef struct RecordManager {
    void *containerA;
    void *containerB;
    u8 pad_08[0x3c];
    u8 refCounts[14];
    u8 useCount;
    u8 pad_53[0x74 - 0x53];
} RecordManager;

extern RecordManager *data_020613d0;
extern const char sMain_DbDbP2_02056198[];
extern const char sMain_DbLanguageP2_020561a4[];
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

BOOL AcquireRecordManager(void)
{
    RecordManager *manager;

    if (data_020613d0 != NULL) {
        data_020613d0->useCount++;
        return TRUE;
    }
    manager = NNSi_FndAllocFromDefaultHeap(sizeof(RecordManager));
    data_020613d0 = manager;
    MI_CpuFill8(manager, 0, sizeof(RecordManager));
    manager->useCount = 1;
    manager->containerA = Msg_OpenContainerAndReadHeader(sMain_DbDbP2_02056198, 0x11, FALSE);
    manager->containerB = Msg_OpenContainerAndReadHeader(sMain_DbLanguageP2_020561a4, 0x11, FALSE);
    return TRUE;
}
