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
    s32 unk_2c;
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
    s8 type;
    u8 pad_01[3];
    s32 speed;
    fx32 duration;
} ShotRecord;

typedef struct {
    u8 pad_00[0x1c];
    fx32 duration;
} ProjectileDef;

typedef struct {
    u8 pad_000[0x138];
    ProjectileDef *def;
    u8 pad_13c[0x14];
    ShotRecord *record;
} SpawnedProjectile;

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
    u8 pad_184[8];
    ShotRecord *records;
    u8 pad_190[4];
    s8 recordType;
    u8 pad_195[3];
    s32 speed;
} SpawnUnit;

extern s16 data_02053580[];
extern EntryInfo *func_ov001_0206db5c(int index);
extern VecFx32 func_ov021_020aed44(SpawnUnit *unit, void *arg);
extern void func_ov021_020ab0ac(SpawnDesc *desc);
extern SpawnedProjectile *func_ov021_020ab0b8(SpawnUnit *unit, SpawnDesc *desc);

void SpawnRecordedProjectile(SpawnUnit *unit, void *arg, SpawnRequest *request)
{
    VecFx32 origin;
    SpawnDesc desc;
    EntryInfo *info;
    SpawnedProjectile *projectile;
    ShotRecord *records;
    ShotRecord *record;
    int slot;
    u16 angle;
    int facing;
    int index;

    info = func_ov001_0206db5c(unit->entryIndex);
    angle = info->facing - 0x8000;
    facing = (u16)(angle + 0x8000);
    origin = func_ov021_020aed44(unit, arg);
    func_ov021_020ab0ac(&desc);
    desc.position = origin;
    index = facing >> 4;
    desc.direction.x = data_02053580[index];
    desc.direction.y = 0;
    desc.direction.z = data_02053580[(0x400 - index) & 0xfff];
    desc.unk_2c = 0;
    desc.count = 1;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = request->kind;
    desc.subKind = request->subKind;
    desc.power = request->power;
    projectile = func_ov021_020ab0b8(unit, &desc);
    if (projectile != NULL) {
        records = unit->records;
        slot = unit->spawnCount;
        record = &records[slot];
        projectile->record = record;
        records[slot].type = unit->recordType;
        record->speed = unit->speed;
        if (unit->speed > 0) {
            record->duration = 0xc000;
        } else {
            record->duration = projectile->def->duration;
        }
        unit->spawnCount++;
        return;
    }
    unit->flags &= ~1;
}
