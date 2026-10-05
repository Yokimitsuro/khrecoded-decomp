#include "nitro/types.h"

typedef struct TableEntry {
    u32 unk_00;
    void *value;
    u32 pad_08[2];
} TableEntry;

typedef struct EntryTable {
    u32 unk_00;
    u32 unk_04;
    TableEntry *entries;
} EntryTable;

typedef struct TableOwner {
    u32 unk_00;
    EntryTable *table;
} TableOwner;

void *GetOwnerTableEntryValue(TableOwner *owner, int index)
{
    EntryTable *table;

    if (owner == NULL) {
        return NULL;
    }
    table = owner->table;
    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index < 0x13) {
        return table->entries[index].value;
    }
    return NULL;
}
