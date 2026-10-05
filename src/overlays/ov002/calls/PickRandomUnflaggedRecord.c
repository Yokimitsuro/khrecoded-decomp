#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0x4];
    s32 isValid;
    s32 itemId;
    u8 pad_0C[0xc];
} RecordB;

extern unsigned int func_0202a9e4(unsigned int range);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern RecordB *GetRecordTableBEntry(s32 index);
extern s32 GetPackedFieldValue(u32 target, s32 category, s32 flag);
extern s32 LookupTableOffset(s32 category, s32 entryIndex);
extern BOOL IsRecordFlagBitSet(s32 recordId);
extern BOOL func_ov002_0206a9f8(s32 recordId);
extern void func_ov002_0206aaa0(s32 *itemIds);
extern int DispatchContextCommand(u32 command, s32 arg, s32 arg2, void *out);

s32 PickRandomUnflaggedRecord(u32 target) {
    s32 chosenId;
    s32 attempt;
    s32 category;
    s32 entry;
    s32 recordId;
    s32 scan;
    s32 itemId;
    s32 preferredIndex;
    RecordB *record;
    int flagged;
    int preferredFlagged;
    s32 preferredItemIds[6];

    category = func_0202a9e4(0x11) + 3;
    if (target != 0) {
        for (attempt = 0; attempt < 0x11; attempt++) {
            entry = GetPackedFieldValue(target, category, 1);
            if (entry != 0) {
                chosenId = LookupTableOffset(category, entry - 1);
                if (!IsRecordFlagBitSet(chosenId)) {
                    DispatchContextCommand(0x8000000c, chosenId, 0, &flagged);
                    return chosenId;
                }
            }
            category++;
            if (category >= 0x14) {
                category = 3;
            }
        }
    }
    AcquireRecordSlot(9, 1);
    if (func_0202a9e4(100) < 0x46) {
        func_ov002_0206aaa0(preferredItemIds);
        for (preferredIndex = 0; preferredIndex < 6; preferredIndex++) {
            itemId = preferredItemIds[preferredIndex];
            recordId = func_0202a9e4(0x541) + 0x60;
            for (scan = 0; scan < 0x541; scan++) {
                record = GetRecordTableBEntry(recordId);
                if (record != NULL && record->isValid != 0 && record->itemId == itemId) {
                    preferredFlagged = IsRecordFlagBitSet(recordId);
                    chosenId = recordId;
                    if (preferredFlagged == 0 && func_ov002_0206a9f8(recordId)) {
                        DispatchContextCommand(0x8000000c, recordId, 0, &preferredFlagged);
                        scan = preferredIndex = 99999;
                    }
                }
                recordId++;
                if (recordId >= 0x5a1) {
                    recordId = 0x60;
                }
            }
        }
    } else {
        recordId = func_0202a9e4(0x541) + 0x60;
        for (attempt = 0; attempt < 0x541; attempt++) {
            record = GetRecordTableBEntry(recordId);
            if (record != NULL && record->isValid != 0) {
                flagged = IsRecordFlagBitSet(recordId);
                chosenId = recordId;
                if (flagged == 0 && func_ov002_0206a9f8(recordId)) {
                    DispatchContextCommand(0x8000000c, recordId, 0, &flagged);
                    attempt = 99999;
                }
            }
            recordId++;
            if (recordId >= 0x5a1) {
                recordId = 0x60;
            }
        }
    }
    ReleaseRecordSlot(9);
    if (!func_ov002_0206a9f8(chosenId)) {
        chosenId++;
        if (chosenId >= 0x5a1) {
            chosenId = 0x61;
        }
    }
    return chosenId;
}
