#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotDesc {
    u8 pad_00[4];
    u8 group;
    u8 variant;
    u8 pad_06[2];
    int duration;
} SlotDesc;

typedef struct EntryInfo {
    u8 pad_000[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct SoundParams {
    VecFx32 position;
    VecFx32 velocity;
    int rangeX;
    int rangeY;
    u8 pad_20[4];
    int rangeZ;
    int duration;
    int delay;
    int variant;
    int group;
    int loop;
    u8 pad_3c[4];
} SoundParams;

typedef struct SoundSlot {
    u8 pad_000[0x100];
    u32 handle;
    int active;
} SoundSlot;

typedef struct SoundLimiter {
    u8 pad_000[0x150];
    SoundSlot *slot;
} SoundLimiter;

typedef struct SoundEmitter {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[2];
    s8 spawnCount;
    u8 flags;
    u8 pad_041[0x178 - 0x41];
    int rangeX;
    int rangeY;
    int rangeZ;
    u8 pad_184[4];
    s16 owner;
} SoundEmitter;

extern void ZeroBytes0x40(void *obj);
extern EntryInfo *GetBoundedEntryField(int index);
extern SoundLimiter *TryConsumeLimitedUse(SoundEmitter *limiter, SoundParams *target);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, SoundParams *params, u32 flags);

void SpawnEmitterSound(SoundEmitter *emitter, u32 unused, SlotDesc *desc)
{
    SoundParams params;
    SoundLimiter *limiter;

    emitter->flags = 0;
    ZeroBytes0x40(&params);
    params.position = GetBoundedEntryField(emitter->entryIndex)->position;
    params.velocity.z = 0;
    params.velocity.y = 0;
    params.velocity.x = 0;
    params.delay = 0;
    params.loop = 0;
    params.rangeX = emitter->rangeX;
    params.rangeY = emitter->rangeY;
    params.rangeZ = emitter->rangeZ;
    params.group = desc->group;
    params.variant = desc->variant;
    params.duration = desc->duration;
    limiter = TryConsumeLimitedUse(emitter, &params);
    if (limiter != NULL) {
        SoundSlot *slot = limiter->slot;
        slot->handle = SpawnSoundSlot(emitter->owner, 0, &params, 0);
        slot->active = 1;
        emitter->spawnCount++;
    }
}
