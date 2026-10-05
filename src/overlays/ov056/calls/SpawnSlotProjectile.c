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
    u8 pad_96[0xbc - 0x96];
    VecFx32 position;
} EntryInfo;

typedef struct {
    u8 pad_00[8];
    s32 active;
} ProjectileState;

typedef struct {
    u8 pad_000[0x150];
    ProjectileState *state;
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
    u8 pad_184[4];
    s16 soundId;
} SpawnUnit;

extern s16 data_02053580[];
extern EntryInfo *GetBoundedEntryField(int index);
extern void func_ov021_020a91d8(VecFx32 *out, int entryIndex, void *arg);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_ov021_020ab0ac(SpawnDesc *desc);
extern SpawnedProjectile *func_ov021_020ab0b8(SpawnUnit *unit, SpawnDesc *desc);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);

void SpawnSlotProjectile(SpawnUnit *unit, void *arg, SpawnRequest *request)
{
    EntryInfo *info;
    SpawnDesc desc;
    MtxFx33 rot;
    VecFx32 offset;
    SpawnedProjectile *projectile;
    u16 angle;
    u16 facing;
    int index;

    unit->flags = 0;
    func_ov021_020ab0ac(&desc);
    info = GetBoundedEntryField(unit->entryIndex);
    angle = info->facing - 0x8000;
    facing = angle + 0x8000;
    func_ov021_020a91d8(&offset, unit->entryIndex, arg);
    index = facing >> 4;
    MTX_RotY33_(&rot, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
    func_01ff9404(&offset, &rot, &offset);
    func_01ff9e0c(&offset, &info->position, &desc.position);
    desc.direction.z = 0;
    desc.direction.y = 0;
    desc.direction.x = 0;
    desc.unk_2c = 0;
    desc.count = 0;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = request->kind;
    desc.subKind = request->subKind;
    desc.power = request->power;
    projectile = func_ov021_020ab0b8(unit, &desc);
    if (projectile != NULL) {
        projectile->state->active = 1;
        unit->spawnCount++;
    }
    SpawnSoundSlot(unit->soundId, 0, &desc.position, 0);
}
