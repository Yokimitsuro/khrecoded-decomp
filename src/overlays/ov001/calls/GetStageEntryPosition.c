#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEntry {
    u8 pad_00[0xb0];
    VecFx32 position;
} StageEntry;

extern StageEntry *func_ov001_02099270(u32 id);

void GetStageEntryPosition(u32 id, VecFx32 *outPosition)
{
    StageEntry *entry = func_ov001_02099270(id);

    if (entry != NULL) {
        *outPosition = entry->position;
    }
}
