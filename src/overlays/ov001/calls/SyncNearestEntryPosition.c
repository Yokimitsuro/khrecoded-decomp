#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageWalker {
    u8 pad_000[0x28c];
    u16 cellIndex : 11;
    u16 entryGroup : 3;
    u16 extra : 2;
    u8 pad_28E[0x32];
    VecFx32 position;
} StageWalker;

extern u16 FindNearestStageEntry(const VecFx32 *target);
extern void SyncStageEntryPosition(u32 id, VecFx32 *outPosition);

void SyncNearestEntryPosition(StageWalker *walker, int unused, VecFx32 *outPosition)
{
    if (FindNearestStageEntry(&walker->position) != 0) {
        SyncStageEntryPosition(walker->entryGroup, outPosition);
    }
}
