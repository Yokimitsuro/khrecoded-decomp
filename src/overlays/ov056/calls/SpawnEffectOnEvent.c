#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x5a];
    u8 kind;
} SourceInfo;

typedef struct {
    u8 pad_00[4];
    SourceInfo *info;
} EventSource;

typedef struct {
    u8 pad_00[8];
    int type;
    VecFx32 position;
    EventSource *source;
} HitEvent;

typedef struct {
    void *slots;
    s8 slotCount;
} EffectPool;

typedef struct {
    u8 pad_000[0x18c];
    EffectPool effectPool;
} EffectOwner;

extern void StartFreeModelSlot(EffectPool *pool, int effectId, VecFx32 *position);

void SpawnEffectOnEvent(EffectOwner *owner, int unused, HitEvent *event)
{
    BOOL spawn = FALSE;

    switch (event->type) {
    case 3:
        if (event->source->info->kind == 1) {
            spawn = TRUE;
        }
        break;
    case 2:
    case 4:
        spawn = TRUE;
        break;
    }
    if (spawn) {
        StartFreeModelSlot(&owner->effectPool, 2, &event->position);
    }
}
