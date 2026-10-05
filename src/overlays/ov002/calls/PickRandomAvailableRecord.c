#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0x8];
    s32 itemId;
    u8 pad_0C[0xc];
} RecordB;

extern u8 data_ov002_0206ada0[];
extern s32 data_ov002_0206aebc[];
extern unsigned int func_0202a9e4(unsigned int range);
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern RecordB *GetRecordTableBEntry(s32 index);
extern BOOL IsRecordFlagBitSet(s32 recordId);
extern BOOL func_ov002_0206a9f8(s32 recordId);

s32 PickRandomAvailableRecord(s32 category, s32 *preferredItemIds) {
    s32 recordId;
    s32 firstId;
    s32 endId;
    s32 recordCount;
    s32 attempt;
    s32 scanIndex;
    s32 preferredIndex;
    RecordB *record;
    s32 categoryIndex;

    if (category < 1 || category >= 0x15 || category == 0x13) {
        return 0;
    }
    categoryIndex = category - 1;
    recordCount = data_ov002_0206ada0[categoryIndex];
    firstId = data_ov002_0206aebc[categoryIndex];
    endId = firstId + recordCount;
    recordId = firstId + func_0202a9e4(recordCount);
    AcquireRecordSlot(9, 1);
    if (preferredItemIds == NULL) {
        for (attempt = 0; attempt < recordCount; attempt++) {
            if (!IsRecordFlagBitSet(recordId)) {
                if (!func_ov002_0206a9f8(recordId)) {
                    continue;
                }
                break;
            }
            recordId++;
            if (recordId >= endId) {
                recordId = firstId;
            }
        }
    } else {
        for (preferredIndex = 0; preferredIndex < 6; preferredIndex++) {
            for (scanIndex = 0; scanIndex < recordCount; scanIndex++) {
                if (!IsRecordFlagBitSet(recordId)) {
                    record = GetRecordTableBEntry(recordId);
                    if (record != NULL && record->itemId == preferredItemIds[preferredIndex] && func_ov002_0206a9f8(recordId)) {
                        preferredIndex = 99999;
                        break;
                    }
                }
                recordId++;
                if (recordId >= endId) {
                    recordId = firstId;
                }
            }
        }
    }
    ReleaseRecordSlot(9);
    while (!func_ov002_0206a9f8(recordId)) {
        recordId++;
        if (recordId >= endId) {
            recordId = firstId;
        }
    }
    return recordId;
}
