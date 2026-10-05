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

typedef struct ListView {
    void (*onChange)(void);
    RowList *rows;
    u8 pad_08[0x68];
    int slots[3];
    u8 pad_7c[0x1c];
    int scrollTarget;
    BOOL scrolling;
    u8 pad_a0[4];
    int selectedIndex;
} ListView;

extern void func_ov025_020b65e4(ListView *list, int startSlot, int *slots);
extern void func_ov025_020b6cc0(ListView *list, int entryIndex);
extern void func_ov025_020b6d20(ListView *list, int entryIndex);

static inline int GetEntryScroll(RowEntry *entries, int index)
{
    entries += index;
    return -((entries->y - 2) * 8);
}

void ResetListToFirstEntry(ListView *list)
{
    RowTable *table = list->rows->table;
    int saved[3] = {0, 0, 0};
    int i;
    int scroll;

    list->selectedIndex = 0;
    for (i = 0; i < 3; i++) {
        saved[i] = list->slots[i];
    }
    func_ov025_020b65e4(list, 0, saved);
    func_ov025_020b6cc0(list, list->selectedIndex);
    func_ov025_020b6d20(list, list->selectedIndex);
    scroll = GetEntryScroll(table->entries, list->selectedIndex);
    list->scrollTarget = (scroll > 0) ? 0 : ((scroll < -256) ? -256 : scroll);
    list->scrolling = TRUE;
    if (list->onChange != NULL) {
        list->onChange();
    }
}
