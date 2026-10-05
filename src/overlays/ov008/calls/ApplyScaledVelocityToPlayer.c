#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PlayerEntry PlayerEntry;

struct PlayerEntry {
    u8 pad_000[0x214];
    void (*applyVelocity)(PlayerEntry *entry, VecFx32 *velocity);
};

typedef struct {
    u8 pad_00[0x6c];
    VecFx32 velocity;
} LaunchSource;

extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern PlayerEntry *GetBoundedEntryField(int index);

BOOL ApplyScaledVelocityToPlayer(void *unused, void *unused2, LaunchSource *source)
{
    VecFx32 velocity;
    VecFx32 scaled = source->velocity;
    PlayerEntry *entry;

    ScaleVecFx32InPlace(&scaled, 0x385);
    velocity = scaled;
    entry = GetBoundedEntryField(0);
    if (entry->applyVelocity != NULL) {
        entry->applyVelocity(entry, &velocity);
    }
    return FALSE;
}
