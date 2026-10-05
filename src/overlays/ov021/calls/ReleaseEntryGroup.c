#include "nitro/types.h"

typedef struct {
    u8 data[0x154];
} GroupEntry;

typedef struct {
    u8 pad_00[8];
    GroupEntry *entries;
    u8 pad_0C[9];
    u8 count;
} EntryGroup;

extern void ReleaseNestedObjectAt0x30(GroupEntry *entry);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseEntryGroup(EntryGroup *group) {
    int i;

    for (i = 0; i < group->count; i++) {
        ReleaseNestedObjectAt0x30(&group->entries[i]);
    }
    NNSi_FndFreeFromDefaultHeap(group->entries);
}
