#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    VecFx32 velocity;
    s32 health;
    s32 attack;
    s32 defense;
    s32 magic;
    fx32 healthRate;
    s32 kind;
    u32 flags;
    s32 level;
    s32 motion;
    s32 typeIndex;
} UnitSpawnDesc;

typedef struct {
    u32 flags;
    u8 pad_04[0x10];
    fx32 speedScale;
    u8 pad_18[0xc];
    s32 startHidden;
    u8 pad_28[0x34];
    s8 maxUnits;
    u8 pad_5d[3];
} UnitType;

typedef struct {
    s8 kind;
    u8 pad_01;
    s8 state;
    u8 pad_03;
    s32 timer;
    s32 health;
    s32 defense;
    s32 magic;
    s32 magicDefense;
    VecFx32 position;
    VecFx32 velocity;
    u8 pad_30[0xa4];
    VecFx32 homePosition;
    u8 pad_e0[0x58];
    UnitType *type;
    s8 typeIndex;
    u8 pad_13d;
    s16 slots[8];
    u8 pad_14e[6];
} Unit;

typedef struct {
    u8 pad_00[8];
    Unit *units;
    UnitType *types;
} UnitManager;

extern void RebindModelAnimTracks(Unit *unit, s32 motion);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void func_01ffafb4(fx32 scale, VecFx32 *src, VecFx32 *dst);

Unit *SpawnUnitFromDesc(UnitManager *mgr, UnitSpawnDesc *desc)
{
    UnitType *type = &mgr->types[desc->typeIndex];
    Unit *unit = NULL;
    int i;
    for (i = 0; i < type->maxUnits; i++) {
        Unit *candidate = &mgr->units[i];
        if (candidate->state == -1) {
            unit = candidate;
            break;
        }
    }
    if (unit == NULL) {
        return NULL;
    }
    unit->homePosition = desc->position;
    RebindModelAnimTracks(unit, desc->motion);
    unit->type = type;
    unit->typeIndex = desc->typeIndex;
    unit->position = desc->position;
    unit->kind = desc->kind;
    if (type->startHidden > 0) { unit->state = 0; } else { unit->state = 1; }
    unit->timer = 0;
    unit->health = desc->health;
    unit->health += FX_Mul(desc->healthRate, unit->health * desc->level) / 100;
    unit->magicDefense = desc->magic;
    unit->magicDefense += unit->magicDefense * desc->level / 100;
    unit->defense = desc->attack;
    if (desc->flags & 1) {
        unit->defense += unit->defense * desc->level / 100;
    }
    unit->magic = desc->defense;
    {
        fx32 velZ = desc->velocity.z;
        fx32 velY = desc->velocity.y;
        fx32 velX = desc->velocity.x;
        unit->velocity.x = velX;
        unit->velocity.y = velY;
        unit->velocity.z = velZ;
    }
    if (!(type->flags & 0x20)) {
        func_01ffafb4(type->speedScale, &unit->velocity, &unit->velocity);
    }
    for (i = 0; i < 8; i++) {
        unit->slots[i] = -1;
    }
    return unit;
}
