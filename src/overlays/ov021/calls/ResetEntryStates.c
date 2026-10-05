#include "nitro/types.h"

typedef struct {
    u8 pad_000[2];
    s8 state;
    u8 pad_003[0x151];
} GroupEntry;

typedef struct {
    u8 pad_00[8];
    GroupEntry *entries;
    u8 pad_0C[9];
    u8 count;
} EntryGroup;

void ResetEntryStates(EntryGroup *group) {
    int i;

    if (group == NULL) {
        return;
    }
    for (i = 0; i < group->count; i++) {
        group->entries[i].state = -1;
    }
}
