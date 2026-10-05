#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[6];
} TableEntry;

typedef struct {
    int count;
    TableEntry *entries;
} EntryTable;

TableEntry *FindTableEntryById(EntryTable *table, int id) {
    int i;
    TableEntry *result = NULL;

    for (i = 0; i < table->count; i++) {
        if (id == table->entries[i].id) {
            result = &table->entries[i];
            break;
        }
    }
    return result;
}
