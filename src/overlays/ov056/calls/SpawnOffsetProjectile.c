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
    u8 pad_00[0x94];
    u16 facing;
    u8 pad_96[0xbc - 0x96];
    VecFx32 position;
} EntryInfo;

typedef struct {
    u8 pad_00[0x10];
    fx32 height;
} UnitShape;

typedef struct {
    u8 pad_00[0xc];
    UnitShape *shape;
    u8 pad_10[0x2c];
    s8 entryIndex;
    u8 pad_3d[2];
    s8 spawnCount;
    s8 flags;
    u8 pad_41[0x137];
    s32 paramA;
    s32 paramB;
    s32 paramC;
} SpawnUnit;

extern const VecFx32 data_ov056_020d7fcc;
extern s16 data_02053580[];
extern EntryInfo *func_ov001_0206db5c(int index);
extern void func_ov021_020ab0ac(SpawnDesc *desc);
extern void func_ov021_020a9180(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void *func_ov021_020ab0b8(SpawnUnit *unit, SpawnDesc *desc);
extern void func_ov021_020af564(int first, int second);

void SpawnOffsetProjectile(SpawnUnit *unit, u32 kind, u32 subKind, s32 power)
{
    EntryInfo *info;
    VecFx32 offset;
    SpawnDesc desc;
    u16 angle;
    int facing;
    int index;

    info = func_ov001_0206db5c(unit->entryIndex);
    offset = data_ov056_020d7fcc;
    unit->flags = 0;
    angle = info->facing - 0x8000;
    facing = (u16)(angle + 0x8000);
    func_ov021_020ab0ac(&desc);
    func_ov021_020a9180(&desc.position, &info->position, facing, &offset);
    desc.position.y -= unit->shape->height / 2;
    index = facing >> 4;
    desc.direction.x = data_02053580[index];
    desc.direction.y = 0;
    desc.direction.z = data_02053580[(0x400 - index) & 0xfff];
    desc.unk_2c = 0;
    desc.count = 1;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = kind;
    desc.subKind = subKind;
    desc.power = power;
    if (func_ov021_020ab0b8(unit, &desc) != NULL) {
        unit->spawnCount++;
    } else {
        unit->flags &= ~1;
    }
    func_ov021_020af564(3, 1);
}
