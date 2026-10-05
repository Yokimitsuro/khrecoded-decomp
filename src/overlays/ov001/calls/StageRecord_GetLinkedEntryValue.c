#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[0x1a];
    u16 linkedEntryIndex;
} StageRecord;

typedef struct LinkedEntry {
    u8 pad_00[0x8];
    s16 value;
} LinkedEntry;

extern int data_ov001_0209f2e8;
extern StageRecord *GetStageEventRecord(u32 id);
extern LinkedEntry *GetSmallTableEntry(int index);

int StageRecord_GetLinkedEntryValue(u32 id)
{
    StageRecord *record;
    LinkedEntry *entry;

    if (data_ov001_0209f2e8 != -1 && (record = GetStageEventRecord(id)) != NULL &&
        record->linkedEntryIndex != 0xffff &&
        (entry = GetSmallTableEntry(record->linkedEntryIndex)) != NULL) {
        return entry->value;
    }
    return 0;
}
