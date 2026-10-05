#include "nitro/types.h"

typedef struct ListEntry {
    u8 pad_00[4];
    u16 id;
} ListEntry;

typedef struct ListWidget {
    u8 pad_00[0x70];
    ListEntry *entries[3];
} ListWidget;

void GetListWidgetEntryIds(ListWidget *list, u16 *ids)
{
    int i;

    for (i = 0; i < 3; i++) {
        ListEntry *entry = list->entries[i];
        if (entry == NULL) {
            break;
        }
        ids[i] = entry->id;
    }
    for (; i < 3; i++) {
        ids[i] = 0xffff;
    }
}
