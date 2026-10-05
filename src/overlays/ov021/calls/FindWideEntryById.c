#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[10];
} WideEntry;

typedef struct {
    int count;
    WideEntry *entries;
} WideTable;

WideEntry *FindWideEntryById(WideTable *table, int id) {
    WideEntry *entry;
    WideEntry *result = NULL;
    int i = 0;

    for (entry = table->entries; i < table->count; i++, entry++) {
        if (entry->id == id) {
            result = entry;
            break;
        }
    }
    return result;
}
