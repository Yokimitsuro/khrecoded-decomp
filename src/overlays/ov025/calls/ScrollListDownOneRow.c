#include "nitro/types.h"

typedef struct RowEntry {
    u16 value;
    u16 y;
    u32 unk_4;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[8];
    RowEntry entries[1];
} RowTable;

typedef struct RowList {
    u8 pad_00[4];
    RowTable *table;
} RowList;

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 firstIndex;
    u16 index;
} SlotRecord;

typedef struct ListView {
    void (*onChange)(void);
    RowList *rows;
    u8 pad_08[0x68];
    SlotRecord *slots[3];
    u8 pad_7c[0x1c];
    int scrollTarget;
    BOOL scrolling;
    int busy;
    int selectedIndex;
} ListView;

extern void func_ov025_020b65e4(ListView *list, int startSlot, SlotRecord **slots);
extern void func_ov025_020b6cc0(ListView *list, int entryIndex);
extern void func_ov025_020b6d20(ListView *list, int entryIndex);

static inline int GetEntryScroll(RowEntry *entries, int index)
{
    entries += index;
    return -((entries->y - 2) * 8);
}

void ScrollListDownOneRow(ListView *list)
{
    RowTable *table = list->rows->table;
    SlotRecord *saved[3] = {NULL, NULL, NULL};
    int i;
    int row;
    int scroll;

    if (list->busy == 0) {
        row = (table->entries[list->selectedIndex].y - 2) / 16;
        if (row < 3 && list->slots[row] != NULL) {
            list->selectedIndex = list->slots[row]->index;
            for (i = row; i < 3; i++) {
                saved[i] = list->slots[i];
            }
            func_ov025_020b65e4(list, row + 1, saved);
            func_ov025_020b6d20(list, list->selectedIndex);
            func_ov025_020b6cc0(list, list->selectedIndex);
            scroll = GetEntryScroll(table->entries, list->selectedIndex);
            if (scroll > 0) {
                scroll = 0;
            } else if (scroll < -256) {
                scroll = -256;
            }
            list->scrollTarget = scroll;
            if (scroll != 0) {
                list->scrolling = TRUE;
            }
            if (list->onChange != NULL) {
                list->onChange();
            }
        }
    }
}
