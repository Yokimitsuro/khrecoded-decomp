#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    u8 pad_04[0x10];
} SlotEntry;

typedef struct {
    u8 pad_00[0x30];
    u8 *resource;
    u8 pad_34[0x8C - 0x34];
} SlotRecord;

typedef struct {
    u8 pad_00[0x18];
    SlotRecord records[1];
} SlotList;

typedef struct {
    u8 pad_0000[0x174];
    u8 slotLists[2][0x6434];
    SlotEntry entries[12];
} Ov103State;

void *GetSlotEntryResource(int listIndex, int entryIndex, Ov103State *state)
{
    SlotList *list = (SlotList *)state->slotLists[listIndex];
    SlotEntry *entry;
    SlotRecord *record;
    int recordIndex;
    u8 *resource;

    if (listIndex == 0) {
        entry = &state->entries[entryIndex];
    } else {
        entry = NULL;
    }
    recordIndex = entry->recordIndex;
    if (recordIndex < 0) {
        return NULL;
    }
    record = &list->records[recordIndex];
    if (record == NULL) {
        return NULL;
    }
    resource = record->resource;
    if (resource == NULL) {
        return NULL;
    }
    resource += 8;
    if (resource == NULL) {
        return NULL;
    }
    return resource;
}
