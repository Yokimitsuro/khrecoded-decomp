#include "nitro/types.h"

extern void *GetRecordTableBEntry(s32 index);
extern s32 IsRecordSlotAcquired(s32 id);
extern void AcquireRecordSlot(s32 id, s32 value);
extern void ReleaseRecordSlot(s32 id);
extern void CopyWideStringBounded(u32 dst, u32 value, u32 maxLen);

void CopyRecordTableBField(s32 index, u32 dst) {
    s32 wasLocked = IsRecordSlotAcquired(9);
    u32 entry;

    if (wasLocked == 0) {
        AcquireRecordSlot(9, 1);
    }
    entry = (u32)GetRecordTableBEntry(index);
    CopyWideStringBounded(dst, *(u32 *)(entry + 0x14), 0x3f);
    if (wasLocked != 0) {
        return;
    }
    ReleaseRecordSlot(9);
}
