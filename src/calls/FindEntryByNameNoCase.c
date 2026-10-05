#include "nitro/types.h"

/* Linear scan of a table for an 8-byte name match. */
extern int PXI_Init_02022af8(void *a, void *b, int len);

typedef struct EntryTable {
    u8 pad_00[0x76];
    u16 entryCount;
    u8 pad_78[0x94 - 0x78];
    u8 *entries;
} EntryTable;

void *FindEntryByNameNoCase(EntryTable *table, void *key)
{
    int i;
    int count;
    int cmpResult;
    u8 *entries;

    count = table->entryCount;
    i = 0;
    if (count > 0) {
        do {
            entries = table->entries;
            cmpResult = PXI_Init_02022af8(entries + i * 0x18, key, 8);
            if (cmpResult == 0) {
                return entries + i * 0x18;
            }
            i = i + 1;
        } while (i < count);
    }
    return NULL;
}
