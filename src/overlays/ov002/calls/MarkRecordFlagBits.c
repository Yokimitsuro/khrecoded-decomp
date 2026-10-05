#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0xc];
    s32 category;
    u8 pad_10[0x8];
} RecordB;

typedef struct RecordFlagSets {
    u8 primaryBits[0x67];
    u8 secondaryBits[0x67];
} RecordFlagSets;

extern u16 data_ov002_0206adb4[];
extern s32 data_ov002_0206aebc[];
extern BOOL IsRecordSlotAcquired(s32 slot);
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern RecordB *GetRecordTableBEntry(s32 index);
extern s32 IsRecordFlagBitSet(s32 recordId);

BOOL MarkRecordFlagBits(RecordFlagSets *flagSets, s32 recordId) {
    s32 byteIndex;
    u8 mask;
    RecordB *record;
    s32 categoryIndex;
    s32 bitIndex;
    BOOL wasAcquired;

    if (IsRecordFlagBitSet(recordId)) {
        return FALSE;
    }
    wasAcquired = IsRecordSlotAcquired(9);
    if (!wasAcquired) {
        AcquireRecordSlot(9, 1);
    }
    record = GetRecordTableBEntry(recordId);
    categoryIndex = record->category - 1;
    bitIndex = data_ov002_0206adb4[categoryIndex] + (recordId - data_ov002_0206aebc[categoryIndex]);
    byteIndex = bitIndex >> 3;
    mask = 1 << (u8)(bitIndex - (byteIndex << 3));
    if (!wasAcquired) {
        ReleaseRecordSlot(9);
    }
    flagSets->primaryBits[byteIndex] |= mask;
    flagSets->secondaryBits[byteIndex] |= mask;
    return TRUE;
}
