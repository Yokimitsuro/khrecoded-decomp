#include "nitro/types.h"

typedef struct LinkEntry {
    s16 recordId;
    s16 valueIndex;
    u8 pad04[8];
} LinkEntry;

typedef struct LinkTable {
    LinkEntry entries[16];
    u32 values[16];
    int count;
} LinkTable;

typedef struct SlotRecord {
    u8 pad00[0x10];
    int state;
    u8 pad14[8];
    u16 baseValue;
} SlotRecord;

u8 *GetOverlaySelectionRecord(u32 selectionIndex);
BOOL AcquireRecordManager(void);
void ReleaseRecordManager(void);
int AcquireRecordSlot(int slot, int param);
BOOL ReleaseRecordSlot(s32 slot);
SlotRecord *GetRecordSlotPair1Entry(s32 index);

void RefreshSelectionLinkValues(void)
{
    LinkTable *table;
    int i = 0;
    table = (LinkTable *)(GetOverlaySelectionRecord(i) + 0x2c);

    AcquireRecordManager();
    AcquireRecordSlot(1, 1);
    for (; i < table->count; i++) {
        LinkEntry *entry = &table->entries[i];
        SlotRecord *record = GetRecordSlotPair1Entry(entry->recordId);
        /* State 3 records are skipped */
        if (record != NULL && record->state != 3)
            table->values[entry->valueIndex] = record->baseValue * 2;
    }
    ReleaseRecordSlot(1);
    ReleaseRecordManager();
}

