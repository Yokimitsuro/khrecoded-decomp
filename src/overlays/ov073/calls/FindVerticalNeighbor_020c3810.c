#include "nitro/types.h"

typedef struct ListEntry {
    u16 unk_0;
    u16 column;
    u16 row;
    u16 unk_6;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[6];
    u16 count;
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 pad_00[4];
    ListTable *table;
} ListData;

typedef struct ListView {
    u8 pad_00[4];
    ListData *data;
    u8 pad_08[0xa0];
    int selectedIndex;
} ListView;

typedef BOOL (*CompareFunc)(int a, int b);

int FindVerticalNeighbor_020c3810(ListView *list, CompareFunc rejectFunc, CompareFunc closerFunc)
{
    ListEntry *best;
    int i;
    int distance;
    ListEntry *entry;
    ListEntry *current;
    int bestIndex;
    ListTable *table;

    table = list->data->table;
    best = NULL;
    bestIndex = -1;
    current = &table->entries[list->selectedIndex];

    for (i = 0; i < table->count; i++) {
        entry = &table->entries[i];
        if (current->column == entry->column) {
            distance = entry->row - current->row;
            if (rejectFunc(distance, 0) == 0) {
                if (best == NULL) {
                    bestIndex = i;
                    best = entry;
                } else if (closerFunc(distance, best->row - current->row) != 0) {
                    bestIndex = i;
                    best = entry;
                }
            }
        }
    }
    return bestIndex;
}
