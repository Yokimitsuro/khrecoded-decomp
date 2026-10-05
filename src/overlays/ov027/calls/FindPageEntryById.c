#include "nitro/types.h"

typedef struct PageEntry {
    u8 pad_00[2];
    u8 id;
} PageEntry;

typedef struct PageTable {
    u8 pad_0000[0x1B9C];
    PageEntry *entries[1];
} PageTable;

PageEntry *FindPageEntryById(PageTable *table, u32 id)
{
    PageEntry **slot = table->entries;

    while ((*slot)->id != id) {
        slot++;
    }
    return *slot;
}
