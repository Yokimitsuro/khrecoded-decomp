#include "nitro/types.h"

typedef struct RecordC {
    u8 pad_00[0x30];
    const u16 *name;
} RecordC;

extern s32 data_ov002_0206aebc[];
extern void CopyRecordTableBField(s32 index, u16 *dst);
extern BOOL IsRecordSlotAcquired(s32 slot);
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern RecordC *GetRecordTableCEntry(s32 index);
extern u16 *CopyWideStringBounded(u16 *dst, const u16 *src, int maxLength);

void CopyRecordName(s32 category, s32 index, u16 *dst)
{
    BOOL wasAcquired;
    s32 base = data_ov002_0206aebc[category];

    if (base != -1) {
        CopyRecordTableBField(base + index, dst);
        return;
    }
    wasAcquired = IsRecordSlotAcquired(10);
    if (!wasAcquired) {
        AcquireRecordSlot(10, 1);
    }
    CopyWideStringBounded(dst, GetRecordTableCEntry(index)->name, 0x3f);
    if (!wasAcquired) {
        ReleaseRecordSlot(10);
    }
}
