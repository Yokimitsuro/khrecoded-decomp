#include "nitro/types.h"

typedef struct {
    int x;
    int y;
    int z;
} EntryVector;

typedef struct {
    u8 pad_000[0x38];
    EntryVector vectors[32];
} GroupEntry;

extern GroupEntry *func_ov032_020bbc80(void *group);

int StoreGroupEntryVector(void *group, EntryVector *vector, int slot)
{
    GroupEntry *entry = func_ov032_020bbc80(group);
    entry->vectors[slot % 32] = *vector;
    return slot + 1;
}
