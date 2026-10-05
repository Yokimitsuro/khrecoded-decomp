#include "nitro/types.h"

typedef struct RecordEntry {
    s32 recordIndex;
    u8 pad_04[0x8];
    u32 flags;
} RecordEntry;

extern u8 *gTextWindowResourceTable;
extern void IndexedRecords_SetFlag2(void *list, int index, int value);

void SetRecordEntryEnabled(RecordEntry *entry, int enabled)
{
    if (enabled) {
        entry->flags |= 1;
    } else {
        entry->flags &= ~1;
    }
    IndexedRecords_SetFlag2(gTextWindowResourceTable + 0x18, entry->recordIndex, enabled);
}
