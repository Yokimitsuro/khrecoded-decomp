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

extern void func_ov021_020aaae8(GroupEntry *entry);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseEntryGroup(EntryGroup *group) {
    int i;

    for (i = 0; i < group->count; i++) {
        func_ov021_020aaae8(&group->entries[i]);
    }
    NNSi_FndFreeFromDefaultHeap(group->entries);
}
