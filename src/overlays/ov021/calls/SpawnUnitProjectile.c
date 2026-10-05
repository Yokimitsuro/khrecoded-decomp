#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    VecFx32 direction;
    s32 paramA;
    s32 paramB;
    s32 pad_20;
    s32 paramC;
    s32 power;
    s32 pad_2c;
    u32 subKind;
    u32 kind;
    s32 count;
    s32 pad_3c;
} SpawnDesc;

typedef struct {
    u8 pad_00[4];
    u8 kind;
    u8 subKind;
    u8 pad_06[2];
    s32 power;
} SpawnRequest;

typedef struct {
    u8 pad_00[0x94];
    u16 facing;
} EntryInfo;

typedef struct {
    u8 pad_00[0x3c];
    s8 entryIndex;
    u8 pad_3d[2];
    s8 spawnCount;
    s8 flags;
    u8 pad_41[0x137];
    s32 paramA;
    s32 paramB;
    s32 paramC;
} SpawnUnit;

extern s16 data_02053580[];
extern EntryInfo *GetBoundedEntryField(int index);
extern VecFx32 func_ov021_020aed44(SpawnUnit *unit, void *arg);
extern void ZeroBytes0x40(SpawnDesc *desc);
extern int TryConsumeLimitedUse(SpawnUnit *unit, SpawnDesc *desc);

void SpawnUnitProjectile(SpawnUnit *unit, void *arg, SpawnRequest *request)
{
    VecFx32 origin;
    SpawnDesc desc;
    EntryInfo *info;
    u16 angle;
    u16 facing;
    int index;

    info = GetBoundedEntryField(unit->entryIndex);
    unit->flags = 0;
    angle = info->facing - 0x8000;
    facing = angle + 0x8000;
    origin = func_ov021_020aed44(unit, arg);
    ZeroBytes0x40(&desc);
    desc.position = origin;
    index = facing >> 4;
    desc.direction.x = data_02053580[index];
    desc.direction.y = 0;
    desc.direction.z = data_02053580[(0x400 - index) & 0xfff];
    desc.count = 1;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = request->kind;
    desc.subKind = request->subKind;
    desc.power = request->power;
    if (TryConsumeLimitedUse(unit, &desc)) {
        unit->spawnCount++;
        return;
    }
    unit->flags &= ~1;
}
