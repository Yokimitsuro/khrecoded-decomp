#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEntry {
    u8 pad_00[0xb0];
    VecFx32 position;
} StageEntry;

extern StageEntry *CacheStageEntryValue(u32 id);

void GetStageEntryPosition(u32 id, VecFx32 *outPosition)
{
    StageEntry *entry = CacheStageEntryValue(id);

    if (entry != NULL) {
        *outPosition = entry->position;
    }
}
