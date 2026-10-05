#include "nitro/types.h"

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    s16 topSlot;
    u8 pad_06;
    u8 visibleCount;
    u8 rowHeight;
    u8 pad_09[0x1f];
} ScrollList;

typedef struct EntryList {
    u8 kind;
} EntryList;

typedef struct Ov081State {
    u8 pad_00[0x62d8];
    u8 visibleIndices[110];
    u8 pad_6346[2];
    u8 *bitIndexTable;
    u8 unseen[110];
    s8 unseenIcons[9];
    u8 visibleCount;
    u8 shownCount;
    u8 unseenIconCount;
} Ov081State;

typedef struct Ov082State {
    ScrollList list;
} Ov082State;

typedef struct IconPos {
    int x;
    int y;
} IconPos;

extern Ov081State *func_ov081_020c5bf8(void);
extern void *func_ov039_020bc1ec(void);
extern void *FindWidgetById(void *container, int id);
extern IconPos *func_ov027_020b91c8(void *container, void *widget);
extern EntryList *GetSlotEntry(int slot);
extern void func_ov082_020bf0ac(Ov082State *state, int row, u8 entry, u8 mode);
extern void IndexedRecord_SetPair(void *container, int icon, IconPos *pos);
extern BOOL AreSlotEntriesAllSeen(int slot);
extern void func_0204f218(void *container, int icon, u16 frame);
extern void IndexedRecord_ClearActive(void *container, int icon);
extern void IndexedRecords_SetFlag2(void *container, int icon, BOOL visible);

void RefreshEntryRows(Ov082State *state)
{
    Ov081State *source = func_ov081_020c5bf8();
    void *container = func_ov039_020bc1ec();
    IconPos *base = func_ov027_020b91c8(container, FindWidgetById(container, 3));
    IconPos pos;
    int row;
    int icon;
    int slot;
    int count;
    int iconCount;
    u8 entry;

    count = source->shownCount;
    for (row = 0, icon = 0; row < count; row++) {
        slot = row + state->list.topSlot;
        entry = source->visibleIndices[slot];
        func_ov082_020bf0ac(state, row, entry, GetSlotEntry(slot)->kind == 2 ? 0 : 2);
        if (source->unseen[slot]) {
            pos = *base;
            pos.y = pos.y + ((row * state->list.rowHeight) << 12);
            IndexedRecord_SetPair(container, source->unseenIcons[icon], &pos);
            if (!AreSlotEntriesAllSeen(slot)) {
                func_0204f218(container, source->unseenIcons[icon], 0);
            } else {
                func_0204f218(container, source->unseenIcons[icon], 1);
            }
            IndexedRecord_ClearActive(container, source->unseenIcons[icon]);
            IndexedRecords_SetFlag2(container, source->unseenIcons[icon], TRUE);
            icon++;
        }
    }
    iconCount = source->unseenIconCount;
    for (; icon < iconCount; icon++) {
        IndexedRecords_SetFlag2(container, source->unseenIcons[icon], FALSE);
    }
}
