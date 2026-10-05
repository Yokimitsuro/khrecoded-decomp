#include "nitro/types.h"

typedef struct SlotGroups {
    u8 pad_000[0x1d4];
    u8 recordSlots[22][16];
    u8 pad_334[0x494 - 0x334];
    u8 counts[22];
    u8 pad_4aa;
    u8 flags_b0 : 3;
    u8 visible : 1;
    u8 flags_b4 : 4;
} SlotGroups;

extern void IndexedRecords_SetFlag2(void *manager, int recordIndex, int visible);

void SetGroupSlotsVisible(void *manager, SlotGroups *groups, int visible)
{
    int group;
    int i;

    groups->visible = (u8)visible;
    for (group = 0; group < 22; group++) {
        for (i = 0; i < groups->counts[group]; i++) {
            IndexedRecords_SetFlag2(manager, groups->recordSlots[group][i], visible);
        }
    }
}
