#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x54];
    fx32 height;
    fx32 gravity;
    s32 lifetime;
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x44];
    s32 layer;
    u8 pad_50[0x10];
} UnitParams;

typedef struct {
    u32 baseId;
    s32 ownerId;
    u8 pad_08[0xc];
    s32 team;
} Spawner;

typedef struct {
    u8 pad_000[0x1c];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[4];
    void *attackCallback;
    void *hitCallback;
    u8 pad_030[0xe];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    u8 pad_18a[2];
    fx32 gravity;
    fx32 launchSpeed;
    fx32 airTime;
    s32 lifetime;
    u8 pad_19c[0x14];
    s32 state;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, SpawnParams *params);
extern void func_ov021_020aecc4(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void func_ov021_020ab030(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern int FX_Mul(int left, int right);
extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void UpdateDelayedSlotProjectile(void);
extern void func_ov056_020d6afc(void);
extern void func_ov021_020ae75c(void);
extern void UpdateFallingProjectile(void);
extern void func_ov021_020aee34(SpawnedUnit *unit, u32 baseId, u32 kind);

SpawnedUnit *SpawnArcUnitFromSpawner(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    SpawnParams spawn;
    fx32 height;
    fx32 gravity;
    fx32 speed;
    UnitParams params;

    unit = AllocEntity(spawner->ownerId, -1, 0x1b4, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24(spawner, &spawn);
    func_ov021_020aecc4(unit, &spawn, &params);
    params.mode = 0x20;
    params.flags = 0;
    params.layer = 2;
    height = spawn.height;
    gravity = spawn.gravity;
    unit->gravity = gravity;
    speed = FX_Sqrt(FX_Mul(height, gravity << 1));
    unit->launchSpeed = speed;
    unit->airTime = FX_Div(speed << 1, gravity);
    unit->lifetime = spawn.lifetime;
    func_ov021_020ab030(unit,
        (spawner->baseId & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        ((spawner->baseId + 2) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        &params, 1, spawner->team);
    unit->updateCallback = UpdateDelayedSlotProjectile;
    unit->drawCallback = func_ov056_020d6afc;
    unit->attackCallback = func_ov021_020ae75c;
    unit->hitCallback = UpdateFallingProjectile;
    func_ov021_020aee34(unit, spawner->baseId, kind);
    unit->state = 0;
    return unit;
}
