#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    s8 state;
    u8 pad_03[0x151];
} EffectEntry;

typedef struct {
    u8 pad_00[8];
    EffectEntry *entries;
    u8 pad_0C[9];
    u8 entryCount;
    u8 pad_16[0x2A];
    s8 flags;
    u8 pad_41[3];
    u16 node[1];
} EffectGroup;

extern void func_ov021_020ab390(EffectEntry *entry);
extern void func_ov021_020ae8ac(u16 *node);

void UpdateActiveEntries(EffectGroup *group)
{
    int i;

    for (i = 0; i < group->entryCount; i++) {
        if (group->entries[i].state != -1) {
            func_ov021_020ab390(&group->entries[i]);
        }
    }
    if (group->flags & 1) {
        func_ov021_020ae8ac(group->node);
    }
}
