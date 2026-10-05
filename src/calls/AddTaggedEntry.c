#include "nitro/types.h"

typedef struct TaggedEntry {
    u32 id : 18;
    u32 order : 6;
    u32 value : 7;
    u32 flag : 1;
} TaggedEntry;

typedef struct TaggedEntryTable {
    TaggedEntry *entries;
    u8 count;
} TaggedEntryTable;

extern TaggedEntry data_02060a50[];

extern void MI_CpuFill8(void *dst, int value, int size);
extern TaggedEntry *FindEntryById(TaggedEntryTable *table, u32 id);

TaggedEntry *AddTaggedEntry(TaggedEntryTable *table, u32 id, int flag, u32 value)
{
    TaggedEntry *entry;
    int i;

    if (table->entries == NULL) {
        table->entries = data_02060a50;
        MI_CpuFill8(data_02060a50, 0, 0x100);
        for (i = 0; i < 0x40; i++) {
            table->entries[i].id = 0x3ffff;
        }
    }
    entry = FindEntryById(table, id);
    if (entry == NULL) {
        entry = &table->entries[table->count];
        entry->id = id;
        entry->order = table->count;
        table->count++;
    }
    entry->value = value;
    entry->flag = flag;
    return entry;
}
