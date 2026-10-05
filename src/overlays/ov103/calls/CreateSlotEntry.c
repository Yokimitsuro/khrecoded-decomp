#include "nitro/types.h"

typedef struct {
    u32 cellId;
    s32 x;
    s32 y;
    s32 visible;
    s32 useAffine;
} SlotTemplate;

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    s32 width;
    s32 height;
} SlotEntry;

typedef struct {
    u8 pad_0000[0x174];
    u8 slotLists[2][0x6434];
    SlotEntry entries[12];
} Ov103State;

extern int PXI_Init_0204f0c8(void *list, u32 cellId, int flags);
extern void func_0204f218(void *list, int recordIndex, u16 frame);
extern void IndexedRecord_ClearActive(void *list, int recordIndex);
extern void Slot_SetMode2Bit(void *list, int recordIndex, int enable);
extern void IndexedRecords_SetFlag2(void *list, int recordIndex, int visible);
extern void IndexedRecord_SetActive(void *list, int recordIndex);
extern void SetSlotPosition_020bf7d4(int listIndex, int entryIndex, int x, int y, Ov103State *state);
extern s16 *GetSlotEntryResource(int listIndex, int entryIndex, Ov103State *state);

void CreateSlotEntry(int listIndex, int entryIndex, SlotTemplate *slotTemplate, Ov103State *state)
{
    void *list = state->slotLists[listIndex];
    SlotEntry *entry;
    int recordIndex;
    s16 *bounds;

    if (listIndex == 0) {
        entry = &state->entries[entryIndex];
    } else {
        entry = NULL;
    }
    recordIndex = PXI_Init_0204f0c8(list, slotTemplate->cellId, 0);
    func_0204f218(list, recordIndex, 0);
    IndexedRecord_ClearActive(list, recordIndex);
    Slot_SetMode2Bit(list, recordIndex, 0);
    IndexedRecords_SetFlag2(list, recordIndex, slotTemplate->visible);
    if (slotTemplate->useAffine != 0) {
        IndexedRecord_SetActive(list, recordIndex);
    }
    entry->recordIndex = recordIndex;
    entry->x = slotTemplate->x;
    entry->y = slotTemplate->y;
    SetSlotPosition_020bf7d4(listIndex, entryIndex, slotTemplate->x, slotTemplate->y, state);
    bounds = GetSlotEntryResource(listIndex, entryIndex, state);
    entry->width = bounds[0] - bounds[2] + 1;
    entry->height = bounds[1] - bounds[3] + 1;
}
