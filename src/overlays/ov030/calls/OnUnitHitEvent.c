#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitEntry HitEntry;
typedef void (*HitCallback)(HitEntry *entry, int value, int kind, int arg);

struct HitEntry {
    u8 pad_000[0x1f0];
    HitCallback onHit;
};

typedef struct {
    u8 pad_00[0x5a];
    u8 isBreakable;
} HitSourceInfo;

typedef struct {
    u8 pad_00[4];
    HitSourceInfo *info;
} HitSource;

typedef struct {
    u8 pad_00[8];
    int type;
    VecFx32 position;
    HitSource *source;
} HitEvent;

typedef struct {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[0x188 - 0x3d];
    s16 hitValue;
    u8 pad_18a[2];
    u8 modelSlots[4];
} HitUnit;

extern HitEntry *GetBoundedEntryField(int index);
extern void StartFreeModelSlot(void *list, int blendIndex, VecFx32 *position);

void OnUnitHitEvent(HitUnit *unit, int arg, HitEvent *event)
{
    HitEntry *entry;
    BOOL triggered = FALSE;
    HitCallback callback;
    int value;

    switch (event->type) {
    case 3:
        if (event->source->info->isBreakable != 1) {
            break;
        }
        triggered = TRUE;
        break;
    case 2:
    case 4:
        triggered = TRUE;
        break;
    }
    if (triggered) {
        entry = GetBoundedEntryField(unit->entryIndex);
        StartFreeModelSlot(unit->modelSlots, 4, &event->position);
        value = unit->hitValue;
        callback = entry->onHit;
        if (callback != NULL) {
            callback(entry, value, 3, 0);
        }
    }
}








