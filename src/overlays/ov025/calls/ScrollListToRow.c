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

typedef struct ScrollList {
    u8 pad_00[4];
    RowList *rows;
    u8 pad_08[0x98];
    int busy;
    int selectedIndex;
} ScrollList;

extern void ScrollListDownOneRow(ScrollList *list);
extern void ScrollListUpOneRow(ScrollList *list);

void ScrollListToRow(ScrollList *list, int targetRow)
{
    int currentRow = (list->rows->table->entries[list->selectedIndex].y - 2) / 16;

    if (list->busy == 0) {
        if (targetRow >= currentRow) {
            for (; currentRow < targetRow; currentRow++) {
                ScrollListDownOneRow(list);
            }
        } else {
            for (; targetRow < currentRow; targetRow++) {
                ScrollListUpOneRow(list);
            }
        }
    }
}
