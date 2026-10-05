#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0x4];
    s32 isValid;
    u8 pad_08[0x4];
    s32 category;
    u8 pad_10[0x8];
} RecordB;

extern u16 data_ov002_0206adb4[];
extern s32 data_ov002_0206aebc[];
extern BOOL IsRecordSlotAcquired(s32 slot);
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern RecordB *GetRecordTableBEntry(s32 index);
extern u8 *func_ov002_02066fb0(void);

s32 IsRecordFlagBitSet(s32 recordId) {
    s32 byteIndex;
    u8 mask;
    RecordB *record;
    s32 categoryIndex;
    s32 bitIndex;
    BOOL wasAcquired;
    u8 *bits;

    wasAcquired = IsRecordSlotAcquired(9);
    if (!wasAcquired) {
        AcquireRecordSlot(9, 1);
    }
    record = GetRecordTableBEntry(recordId);
    if (record->isValid == 0) {
        return -1;
    }
    categoryIndex = record->category - 1;
    bitIndex = data_ov002_0206adb4[categoryIndex] + (recordId - data_ov002_0206aebc[categoryIndex]);
    byteIndex = bitIndex >> 3;
    mask = 1 << (u8)(bitIndex - (byteIndex << 3));
    if (!wasAcquired) {
        ReleaseRecordSlot(9);
    }
    bits = func_ov002_02066fb0();
    if ((mask & bits[byteIndex]) == 0) {
        return FALSE;
    }
    return TRUE;
}
