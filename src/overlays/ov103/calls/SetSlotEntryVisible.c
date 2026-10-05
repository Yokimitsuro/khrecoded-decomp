#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    u8 pad_04[0x10];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x174];
    u8 slotLists[2][0x6434];
    SlotEntry entries[12];
} Ov103State;

extern void IndexedRecords_SetFlag2(void *recordBase, int recordIndex, int visible);

void SetSlotEntryVisible(int listIndex, int entryIndex, int visible, Ov103State *state)
{
    SlotEntry *entry;

    if (listIndex == 0) {
        entry = &state->entries[entryIndex];
    } else {
        entry = NULL;
    }
    IndexedRecords_SetFlag2(state->slotLists[listIndex], entry->recordIndex, visible);
}
