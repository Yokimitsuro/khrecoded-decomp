#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LauncherInfo LauncherInfo;
typedef u32 (*InfoStateGetter)(LauncherInfo *info);
typedef void (*InfoSoundCallback)(LauncherInfo *info, int soundId, int kind, int flags);

struct LauncherInfo {
    u8 pad_000[0x94];
    u16 facing;
    u8 pad_096[0xbc - 0x96];
    VecFx32 position;
    u8 pad_0c8[0x1f0 - 0xc8];
    InfoSoundCallback onSoundStop;
    u8 pad_1f4[0x21c - 0x1f4];
    InfoStateGetter getState;
};

typedef struct {
    u8 pad_000[2];
    s8 phase;
    u8 pad_003[0x154 - 3];
} LauncherEntry;

typedef struct Launcher Launcher;
typedef BOOL (*EntryHandler)(Launcher *unit, LauncherEntry *entry, fx32 step);

struct Launcher {
    u8 pad_000[8];
    LauncherEntry *entries;
    u8 pad_00c[9];
    u8 entryCount;
    u8 pad_016[0x12];
    EntryHandler handlers[5];
    s8 entryIndex;
    u8 pad_03d[2];
    s8 activeCount;
    s8 animFlags;
    u8 pad_041[3];
    u16 animState;
    s16 animIndex;
    u8 pad_048[0xc0 - 0x48];
    u16 rotY;
    u8 pad_0c2[0xe8 - 0xc2];
    VecFx32 position;
    u8 pad_0f4[0x150 - 0xf4];
    u8 blendTable[0x38];
    s16 soundId;
    u8 pad_18a[2];
    u8 slots[8];
    VecFx32 offset;
    u8 pad_1a0[4];
    s32 spawnTimer;
    u8 pad_1a8[8];
    s8 mode;
    u8 pad_1b1[3];
    s32 timer;
    s32 spawnInterval;
    s32 duration;
    u8 pad_1c0[4];
    u32 soundHandle;
    s32 unk_1c8;
};

extern LauncherInfo *GetBoundedEntryField(int index);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern BOOL StepEffectAnimation(Launcher *unit, fx32 step);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern void RebindAnimTracks_020aef84(u16 *tracks, void *blendTable, int blendIndex);
extern void StopSoundSeqHandle(u32 handle);
extern void Handle_WritePayloadIfLive(u32 handle, VecFx32 *src);
extern void SpawnTiltedProjectile(Launcher *unit);
extern void AdvanceModelSlotAnimations(void *slots, fx32 step);

static inline void NotifySoundStop(LauncherInfo *info, int soundId, int kind, int flags)
{
    if (info->onSoundStop != NULL) {
        info->onSoundStop(info, soundId, kind, flags);
    }
}

void UpdateCarriedLauncher(Launcher *unit, fx32 step)
{
    int i;
    LauncherInfo *info = GetBoundedEntryField(unit->entryIndex);
    BOOL finished = FALSE;
    u32 state;
    LauncherEntry *entry;
    u16 angle;
    int rotation;
    VecFx32 pos;
    VecFx32 rotated;

    if (info->getState != NULL) {
        state = info->getState(info);
    } else {
        state = finished;
    }
    if ((state & 0x12) && unit->mode != 0 && unit->mode != 3) {
        unit->mode = 3;
    }
    for (i = 0; i < unit->entryCount; i++) {
        entry = &unit->entries[i];
        if (entry->phase != -1) {
            unit->handlers[entry->phase](unit, entry, step);
        }
    }
    if (unit->mode != 3) {
        angle = info->facing - 0x8000;
        rotation = (u16)(angle + 0x8000);
        RotateOffsetAroundY(&rotated, &info->position, rotation, &unit->offset);
        pos = rotated;
        *(VecFx32 *)&unit->position = *(VecFx32 *)&pos;
        unit->rotY = rotation;
        unit->animState |= 0x20;
    }
    if (StepEffectAnimation(unit, step)) {
        finished = TRUE;
        if (unit->mode != 0) {
            if (unit->animIndex == 0) {
                finished = FALSE;
                if (unit->soundHandle == 0) {
                    unit->soundHandle = SpawnSoundSlot(unit->soundId, 2, &unit->position, finished);
                }
                RebindAnimTracks_020aef84(&unit->animState, unit->blendTable, 1);
                unit->animFlags |= 1;
            } else if (unit->animIndex == 1) {
                unit->animFlags |= 1;
                finished = FALSE;
                if (unit->mode == 3) {
                    StopSoundSeqHandle(unit->soundHandle);
                    unit->soundHandle = finished;
                    NotifySoundStop(info, unit->soundId, 1, finished);
                    RebindAnimTracks_020aef84(&unit->animState, unit->blendTable, 2);
                }
            }
        }
    }
    if (unit->soundHandle != 0) {
        Handle_WritePayloadIfLive(unit->soundHandle, &unit->position);
    }
    switch (unit->mode) {
    case 1:
        unit->timer += step;
        unit->spawnTimer += step;
        if (unit->spawnTimer >= unit->spawnInterval) {
            SpawnTiltedProjectile(unit);
        }
        if (unit->timer >= unit->duration) {
            unit->mode = 2;
        }
        break;
    case 2:
        unit->unk_1c8 = 0;
        unit->mode = 3;
        break;
    case 3:
        if (finished) {
            unit->mode = 0;
            unit->activeCount--;
        }
        break;
    }
    AdvanceModelSlotAnimations(unit->slots, step);
}
