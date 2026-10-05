#include "nitro/types.h"

typedef struct TableEntry {
    u16 id;
    u8 active;
    u8 pad_03;
    u32 value;
    u32 timer;
} TableEntry;

typedef struct EntryTable {
    u8 pad_00[5];
    u8 flags;
    u8 pad_06[0xa];
    TableEntry *entries[1];
} EntryTable;

extern EntryTable *data_ov001_020a04fc;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReallocTableEntry(int index, u16 id)
{
    EntryTable *table = data_ov001_020a04fc;

    if (table->entries[index] != NULL) {
        NNSi_FndFreeFromDefaultHeap(table->entries[index]);
    }
    table->entries[index] = NNSi_FndAllocFromDefaultHeap(sizeof(TableEntry));
    table->entries[index]->id = id;
    table->entries[index]->active = 0;
    table->entries[index]->value = 0;
    table->entries[index]->timer = 0;
    table->flags |= 2;
}
