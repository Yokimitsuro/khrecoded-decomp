#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotGroups {
    u8 pad_000[0x10];
    fx32 scaleX;
    fx32 scaleY;
    u8 pad_018[0x1d4 - 0x18];
    u8 recordSlots[22][16];
    u8 pad_334[0x494 - 0x334];
    u8 counts[22];
} SlotGroups;

extern void SlotTable_SetEntryPair(void *manager, int recordIndex, fx32 scaleX, fx32 scaleY);

void SetGroupSlotsScale(void *manager, SlotGroups *groups, fx32 scaleX, fx32 scaleY)
{
    int group;
    int i;
    fx32 x = (fx32)(((s64)groups->scaleX * scaleX + 0x800) >> 12);
    fx32 y = (fx32)(((s64)groups->scaleY * scaleY + 0x800) >> 12);

    for (group = 0; group < 22; group++) {
        for (i = 0; i < groups->counts[group]; i++) {
            SlotTable_SetEntryPair(manager, groups->recordSlots[group][i], x, y);
        }
    }
}
