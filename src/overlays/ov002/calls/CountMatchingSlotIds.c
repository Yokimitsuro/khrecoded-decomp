#include "nitro/types.h"

extern u32 func_ov002_02066fc8(void);
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern void CollectRecordItemsBySlot(u32 source, s32 *outIds);

s32 CountMatchingSlotIds(u32 other) {
    s32 matchCount = 0;
    u32 current = func_ov002_02066fc8();
    s32 ids[2][16];
    s32 index;

    AcquireRecordSlot(9, 1);
    CollectRecordItemsBySlot(current, ids[0]);
    CollectRecordItemsBySlot(other, ids[1]);
    for (index = 0; index < 16; index++) {
        if (ids[0][index] != -1 && ids[0][index] == ids[1][index]) {
            matchCount++;
        }
    }
    ReleaseRecordSlot(9);
    return matchCount;
}
