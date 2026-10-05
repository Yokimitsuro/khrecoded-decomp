#include "nitro/types.h"

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct SlotGroups {
    Position origin;
    Position offset;
    u8 pad_010[0x1d4 - 0x10];
    u8 recordSlots[22][16];
    u8 pad_334[0x494 - 0x334];
    u8 counts[22];
} SlotGroups;

extern void IndexedRecord_SetPair(void *manager, int recordIndex, Position *position);

void SetGroupSlotsPosition(void *manager, SlotGroups *groups, int group, Position *base)
{
    Position position;
    int i;

    position.x = base->x + (groups->origin.x + groups->offset.x);
    position.y = base->y + (groups->origin.y + groups->offset.y);
    for (i = 0; i < groups->counts[group]; i++) {
        IndexedRecord_SetPair(manager, groups->recordSlots[group][i], &position);
    }
}
