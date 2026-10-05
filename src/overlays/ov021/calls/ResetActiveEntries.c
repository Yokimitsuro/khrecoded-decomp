#include "nitro/types.h"

typedef struct TrackEntry {
    s8 id;
    u8 pad_01[0x1F];
    s32 value;
} TrackEntry;

typedef struct TrackOwner {
    u8 pad_00[0x3E];
    s8 entryCount;
    u8 pad_3F[0x18C - 0x3F];
    TrackEntry *entries;
} TrackOwner;

extern void ResetCountsAndSlots(TrackOwner *owner);

void ResetActiveEntries(TrackOwner *owner)
{
    int index;

    ResetCountsAndSlots(owner);
    for (index = 0; index < owner->entryCount; index++) {
        TrackEntry *entry = &owner->entries[index];
        if (entry->id >= 0) {
            entry->id = -1;
            entry->value = 0;
        }
    }
}
