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

typedef struct EntryInfo EntryInfo;
struct EntryInfo {
    u8 pad_000[0x94];
    u16 facing;
    u8 pad_096[0xbc - 0x96];
    VecFx32 position;
    u8 pad_0c8[0x1f0 - 0xc8];
    void (*onFire)(EntryInfo *info, int value, int a, int b);
    u8 pad_1f4[0x228 - 0x1f4];
    int (*getAimPoint)(EntryInfo *info, VecFx32 *out);
};

typedef struct {
    u8 pad_00[0x18];
    fx32 speed;
} ShotConfig;

typedef struct {
    s32 targetIndex;
    u8 pad_004[8];
    ShotConfig *config;
    u8 pad_010[0x2c];
    s8 entryIndex;
    u8 pad_03d[2];
    s8 spawnCount;
    s8 flags;
    u8 pad_041[0x178 - 0x41];
    s32 paramA;
    s32 paramB;
    s32 paramC;
    u8 pad_184[4];
    s16 fireValue;
    u8 pad_18a[6];
    fx32 lift;
    fx32 length;
} SpawnUnit;

extern const s16 data_02053580[];
extern EntryInfo *GetBoundedEntryField(int index);
extern void GetSelectionSlotPosition(VecFx32 *out, u32 selectionIndex, int slot);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void DivideVecByLength(VecFx32 *vec, fx32 length);
extern void ZeroBytes0x40(SpawnDesc *desc);
extern int TryConsumeLimitedUse(SpawnUnit *unit, SpawnDesc *desc);

void FireAimedSlotProjectile(SpawnUnit *unit, int slot, s32 kind, s32 subKind, s32 power)
{
    MtxFx33 rot;
    VecFx32 origin;
    VecFx32 aim;
    VecFx32 dir;
    SpawnDesc desc;
    void (*onFire)(EntryInfo *, int, int, int);
    int fireValue;
    EntryInfo *info;
    EntryInfo *target;
    u16 angle;
    u16 facing;
    int index;
    s16 cosVal;
    s16 sinVal;
    int found;

    info = GetBoundedEntryField(unit->entryIndex);
    GetSelectionSlotPosition(&origin, unit->entryIndex, slot);
    angle = info->facing - 0x8000;
    facing = angle + 0x8000;
    index = facing >> 4;
    sinVal = data_02053580[(0x400 - index) & 0xfff];
    cosVal = data_02053580[index];
    MTX_RotY33_(&rot, cosVal, sinVal);
    MTX_MultVec33(&origin, &rot, &origin);
    VEC_Add(&origin, &info->position, &origin);
    target = GetBoundedEntryField(unit->targetIndex);
    if (target->getAimPoint != NULL) {
        found = target->getAimPoint(target, &aim);
    } else {
        found = 0;
    }
    if (!found) {
        dir.x = cosVal;
        dir.z = sinVal;
        dir.y = 0;
        VEC_MultAdd(unit->config->speed, &dir, &info->position, &aim);
    }
    VEC_Subtract(&aim, &origin, &dir);
    DivideVecByLength(&dir, unit->length);
    dir.y += unit->lift;
    ZeroBytes0x40(&desc);
    desc.position = origin;
    desc.direction = dir;
    desc.unk_2c = 0;
    desc.count = 1;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = kind;
    desc.subKind = subKind;
    desc.power = power;
    if (TryConsumeLimitedUse(unit, &desc)) {
        unit->spawnCount++;
    } else {
        unit->flags &= ~1;
    }
    fireValue = unit->fireValue;
    onFire = info->onFire;
    if (onFire != NULL) {
        onFire(info, fireValue, 0, 0);
    }
}
