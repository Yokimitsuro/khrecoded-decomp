#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackedEntry {
    u32 flags;
    u8 pad_04[0x4c - 0x04];
    VecFx32 position;
} TrackedEntry;

typedef struct EntryOwner {
    u8 pad_000[0x6b8];
    TrackedEntry *entries;
    s32 entryIndices[1];
} EntryOwner;

void GetAttachmentOffset(VecFx32 *out, EntryOwner *owner, int slot)
{
    VecFx32 position;
    int entryIndex;

    position.z = 0;
    position.y = 0;
    position.x = 0;
    entryIndex = owner->entryIndices[slot];
    if (entryIndex != -1 && entryIndex != -2) {
        if (!(owner->entries[entryIndex].flags & 4)) {
            position = owner->entries[entryIndex].position;
        }
    }
    *out = position;
}
