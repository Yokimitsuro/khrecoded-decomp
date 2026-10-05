#include "nitro/types.h"

typedef struct SceneGroup SceneGroup;

typedef struct {
    u8 pad_000[2];
    s8 state;
    u8 pad_003[0x151];
} SceneEntry;

typedef BOOL (*EntryHandler)(SceneGroup *group, SceneEntry *entry, s32 step);

struct SceneGroup {
    u8 pad_00[8];
    SceneEntry *entries;
    u8 pad_0c[9];
    u8 entryCount;
    u8 pad_16[0x12];
    EntryHandler handlers[5];
    u8 pad_3c[3];
    s8 pendingCount;
};

extern void StepEffectAnimation(SceneGroup *group, s32 step);

void UpdateSceneGroupEntries(SceneGroup *group, s32 step)
{
    int i;

    for (i = 0; i < group->entryCount; i++) {
        SceneEntry *entry = &group->entries[i];
        if (entry->state != -1 && group->handlers[entry->state](group, entry, step)) {
            group->pendingCount--;
        }
    }
    StepEffectAnimation(group, step);
}
