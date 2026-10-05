#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 actorId;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    fx32 blendRate;
    fx32 extraParam;
    fx32 paramA;
    fx32 paramB;
    s8 blendIndex;
    s8 mode;
    u16 flags;
    s16 soundArc;
    s16 soundIndex;
} EntrySpawnDesc;

typedef struct {
    u8 active;
    s8 actorId;
    s8 mode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[2];
    u16 nodeFlags;
    u8 pad_0a[0x7a];
    u16 pitch;
    u16 yaw;
    u8 pad_88[0x24];
    VecFx32 position;
    fx32 scale[3];
    u8 pad_c4[0x48];
    fx32 blendRate;
    u8 pad_110[4];
    u32 soundHandle;
    fx32 paramA;
    VecFx32 offset;
    union {
        u16 angle;
        fx32 x;
    } range;
    fx32 rangeY;
    fx32 paramA2;
    fx32 paramB2;
} SpawnEntry;

extern void SelectModelTrackBlends(SpawnEntry *entry, int blendIndex);
extern void func_ov021_020a87a4(SpawnEntry *entry, int yaw, int pitch);
extern VecFx32 ResolveEntryAnchorPosition(SpawnEntry *entry);
extern s32 func_ov001_02063a38(void);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);

void InitEntryFromDesc(SpawnEntry *entry, EntrySpawnDesc *desc)
{
    entry->active = 1;
    entry->mode = desc->mode;
    entry->flags = desc->flags;
    entry->actorId = desc->actorId;
    entry->soundHandle = 0;
    entry->blendRate = desc->blendRate;
    if (entry->blendRate != FX32_ONE) {
        entry->flags |= 0x100;
    }
    SelectModelTrackBlends(entry, desc->blendIndex);
    switch (entry->mode) {
    case 4:
    case 5:
        entry->paramA = desc->paramA;
    case 0:
        if (entry->mode != 5) {
            entry->position = desc->position;
            entry->yaw = 0;
            entry->nodeFlags |= 0x20;
            if (entry->flags & 0x10) {
                entry->yaw = desc->angle;
                entry->nodeFlags |= 0x20;
            } else if (entry->flags & 8) {
                func_ov021_020a87a4(entry, 0, desc->angle);
            } else {
                entry->pitch = desc->angle;
                entry->nodeFlags |= 0x20;
            }
            entry->scale[0] = entry->scale[1] = entry->scale[2] = desc->scale;
            break;
        }
    case 1:
        entry->offset = desc->position;
        entry->range.angle = desc->angle;
        entry->scale[0] = entry->scale[1] = entry->scale[2] = desc->scale;
        break;
    case 2:
        entry->position = desc->position;
        entry->pitch = desc->angle;
        entry->nodeFlags |= 0x20;
        entry->scale[0] = entry->scale[1] = entry->scale[2] = desc->scale;
        entry->offset.x = desc->extraParam;
        break;
    case 3:
        if (entry->flags & 0x20) {
            entry->range.x = desc->position.x;
            entry->rangeY = desc->position.y;
        } else {
            entry->flags |= 2;
            entry->offset = desc->position;
        }
        entry->paramA2 = desc->paramA;
        entry->paramB2 = desc->paramB;
        entry->scale[0] = entry->scale[1] = entry->scale[2] = desc->scale;
        break;
    }
    if (desc->soundArc != -1 && desc->soundIndex != -1) {
        VecFx32 position = ResolveEntryAnchorPosition(entry);
        int soundFlags = 0;

        if (func_ov001_02063a38() != 4 && (entry->flags & 0x40)) {
            soundFlags |= 5;
        }
        entry->soundHandle = SpawnSoundSlot(desc->soundArc, desc->soundIndex, &position, (u16)soundFlags);
    }
}
