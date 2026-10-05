#include "nitro/types.h"

typedef struct ElementGroups {
    u8 pad_000[0x1d4];
    u8 members[44][16];
    u8 counts[44];
} ElementGroups;

extern void IndexedRecords_SetFlag2(void *panel, int index, int value);

void ApplyGroupElements(void *panel, ElementGroups *groups, int group, int value)
{
    int i;
    for (i = 0; i < groups->counts[group]; i++) {
        IndexedRecords_SetFlag2(panel, groups->members[group][i], value);
    }
}
