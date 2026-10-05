#include "nitro/types.h"

typedef struct TaggedEntry {
    u32 id : 18;
    u32 order : 6;
    u32 value : 7;
    u32 flag : 1;
} TaggedEntry;

typedef struct TaggedEntryTable {
    TaggedEntry *entries;
    u8 count;
} TaggedEntryTable;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x13b];
    TaggedEntryTable taggedEntries;
} OverlaySelectionRecord;

extern int data_020608c8[];
extern TaggedEntry *data_02060940[];

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern TaggedEntry *FindEntryById(TaggedEntryTable *table, u32 id);
extern TaggedEntry *AddTaggedEntry(TaggedEntryTable *table, u32 id, int flag, u32 value);

void RegisterTaggedEntry(u32 id)
{
    OverlaySelectionRecord *record = GetOverlaySelectionRecord(0);
    TaggedEntry *entry;

    if (FindEntryById(&record->taggedEntries, id) != NULL) {
        return;
    }
    entry = AddTaggedEntry(&record->taggedEntries, id, 0, 0);
    data_02060940[data_020608c8[1]] = entry;
    data_020608c8[1]++;
}
