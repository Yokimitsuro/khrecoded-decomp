#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 unk_08;
} RecordB;

extern u8 data_0205347c[];
extern s32 data_02053530[];
extern u32 func_0202a9e4(u32 range);
extern int func_02027808(s32 recordIndex, s32 *outByteIndex, u8 *outMask);
extern BOOL IsValueInTable(s32 value);
extern RecordB *GetRecordTableBEntry(s32 index);

s32 PickRandomRecordInCategory(s32 category, s32 requiredTag)
{
    s32 recordIndex;
    s32 first;
    s32 end;
    s32 count;
    s32 attempt;
    s32 slot;

    if (category < 1 || category == 0x13) {
        return -1;
    }
    slot = category - 1;
    count = data_0205347c[slot];
    first = data_02053530[slot];
    end = first + count;
    recordIndex = first + func_0202a9e4(count);
    for (attempt = 0; attempt < count; attempt++) {
        if (func_02027808(recordIndex, NULL, NULL) == 0 && IsValueInTable(recordIndex)) {
            if (requiredTag == -1) {
                break;
            } else {
                RecordB *record = GetRecordTableBEntry(recordIndex);
                if (record->unk_08 == requiredTag) {
                    break;
                }
            }
        }
        recordIndex++;
        if (recordIndex >= end) {
            recordIndex = first;
        }
    }
    while (!IsValueInTable(recordIndex)) {
        recordIndex++;
        if (recordIndex >= end) {
            recordIndex = first;
        }
    }
    return recordIndex;
}
