#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    s32 x;
    s32 y;
    s32 z;
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x30];
    s32 layer;
    u8 pad_3c[0x24];
} UnitParams;

typedef struct {
    u32 baseId;
    s32 ownerId;
    u8 pad_08[0xc];
    s32 team;
} Spawner;

typedef struct {
    u8 pad_00[8];
    s32 active;
} PartRecord;

typedef struct {
    u8 pad_000[0x150];
    PartRecord *record;
} UnitPart;

typedef struct {
    u8 pad_000[0x8];
    UnitPart *parts;
    u8 pad_00c[0x9];
    u8 partCount;
    u8 pad_016[0x6];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[8];
    void *hitCallback;
    u8 pad_030[0xe];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    u8 pad_18a[2];
    s32 x;
    s32 y;
    s32 z;
    PartRecord *records;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern void UpdateGroupAngles(void);
extern void UpdateSceneGroupEntries(void);
extern void UpdateBurstProjectile(void);
extern void LoadUnitSharedRecords(SpawnedUnit *unit, u32 baseId, u32 kind);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

SpawnedUnit *SpawnPartRecordUnit(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    int i;
    SpawnParams spawn;
    UnitParams params;

    unit = AllocEntity(spawner->ownerId, -1, 0x19c, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24(spawner, &spawn);
    InitializeUnitParameters(unit, &spawn, &params);
    i = 0;
    params.mode = 0x20;
    params.mode |= 0x1006;
    params.layer = 2;
    params.flags = 0;
    unit->x = spawn.x;
    unit->y = spawn.y;
    unit->z = spawn.z;
    SetupOwnerAndEntries(unit,
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (spawner->baseId & 0x1ff),
        ((spawner->baseId + 2) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        &params, 1, spawner->team);
    unit->drawCallback = UpdateGroupAngles;
    unit->updateCallback = UpdateSceneGroupEntries;
    unit->hitCallback = UpdateBurstProjectile;
    LoadUnitSharedRecords(unit, spawner->baseId, kind);
    unit->records = NNSi_FndAllocFromDefaultHeap(unit->partCount * sizeof(PartRecord));
    for (; i < unit->partCount; i++) {
        PartRecord *record = &unit->records[i];
        unit->parts[i].record = record;
        record->active = 0;
    }
    return unit;
}
