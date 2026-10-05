#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    s32 lifetime;
    u8 pad_58[8];
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x58];
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
    u8 pad_024[8];
    void *hitCallback;
    u8 pad_030[0xe];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    u8 pad_18a[2];
    s32 lifetime;
    u8 pad_190[4];
    s32 timer;
    s32 phase;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern void DrawSpinGroupEntries(void);
extern void UpdateTimedUnitEntries(void);
extern void AdvanceLinkedHitUnit(void);
extern void LoadUnitSharedRecords(SpawnedUnit *unit, u32 baseId, u32 kind);

SpawnedUnit *SpawnTimedUnitFromSpawner(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    SpawnParams spawn;
    UnitParams params;

    unit = AllocEntity(spawner->ownerId, -1, 0x1a8, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24(spawner, &spawn);
    InitializeUnitParameters(unit, &spawn, &params);
    params.mode = 0x1006;
    params.flags = 2;
    SetupOwnerAndEntries(unit,
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (spawner->baseId & 0x1ff),
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | ((spawner->baseId + 2) & 0x1ff),
        &params, 1, spawner->team);
    unit->drawCallback = DrawSpinGroupEntries;
    unit->updateCallback = UpdateTimedUnitEntries;
    unit->hitCallback = AdvanceLinkedHitUnit;
    unit->lifetime = spawn.lifetime;
    unit->phase = 0;
    unit->timer = 0;
    LoadUnitSharedRecords(unit, spawner->baseId, kind);
    return unit;
}
