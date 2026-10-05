#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    VecFx32 position;
    VecFx32 direction;
    s32 paramA;
    s32 paramB;
    s32 pad_20;
    s32 paramC;
    s32 power;
    s32 unk_2c;
    s32 subKind;
    s32 kind;
    s32 count;
    s32 pad_3c;
} SpawnDesc;

typedef struct {
    u8 pad_00[0x94];
    u16 facing;
} EntryInfo;

typedef struct {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[0xe8 - 0x3d];
    VecFx32 position;
    u8 pad_0f4[0x178 - 0xf4];
    s32 paramA;
    s32 paramB;
    s32 paramC;
    u8 pad_184[0x1a4 - 0x184];
    s32 cooldown;
    s8 kind;
    s8 subKind;
    u8 pad_1aa[2];
    s32 power;
    u8 pad_1b0[0x1c8 - 0x1b0];
    s32 spawnResult;
} SpawnUnit;

extern const s16 data_02053580[];
extern EntryInfo *GetBoundedEntryField(int index);
extern void ZeroBytes0x40(SpawnDesc *desc);
extern int TryConsumeLimitedUse(SpawnUnit *unit, SpawnDesc *desc);
extern int random_next_scaled(int range);
extern void MTX_RotZ33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);

void SpawnTiltedProjectile(SpawnUnit *unit)
{
    SpawnDesc desc;
    MtxFx33 rot;
    EntryInfo *info;
    u16 angle;
    u16 facing;
    u16 tilt;
    int index;

    info = GetBoundedEntryField(unit->entryIndex);
    angle = info->facing - 0x8000;
    facing = angle + 0x8000;
    ZeroBytes0x40(&desc);
    desc.count = 3;
    desc.position = unit->position;
    index = facing >> 4;
    desc.direction.x = data_02053580[index];
    desc.direction.y = 0;
    desc.direction.z = data_02053580[(0x400 - index) & 0xfff];
    tilt = random_next_scaled(0x1c70) - 0x1c70;
    if (desc.direction.x < 0) {
        tilt = 0xffff - tilt;
    }
    index = tilt >> 4;
    MTX_RotZ33_(&rot, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
    MTX_MultVec33(&desc.direction, &rot, &desc.direction);
    desc.unk_2c = 0;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = unit->kind;
    desc.subKind = unit->subKind;
    desc.power = unit->power;
    unit->spawnResult = TryConsumeLimitedUse(unit, &desc);
    unit->cooldown = 0;
}
