#include "nitro/types.h"

#define ARCHIVE_FILE_KEY(id) (0x80000000 | (((func_ov001_0206dba0(0) + 0x8000) & 0xFFFFFC) << 7) | ((id) & 0x1ff))

typedef struct {
    u8 pad_00[0x54];
    s32 mode;
    s32 range;
    u8 pad_5c[4];
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x44];
    s32 field_4c;
    u8 pad_50[0x10];
} UnitParams;

typedef struct {
    s32 resourceId;
    u32 animationKey;
    s32 slotCount;
    u32 modelKey;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u32 baseId;
    s32 ownerId;
    u8 pad_08[0xc];
    s32 team;
} Spawner;

typedef struct {
    u8 data[0xc];
} TeamRecord;

typedef struct {
    u8 pad_000[0x1c];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[4];
    void *callback_28;
    void *hitCallback;
    u8 pad_030[4];
    void *callback_34;
    void *callback_38;
    u8 pad_03c[2];
    s8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    u8 pad_18a[2];
    TeamRecord *records;
    s16 effectGroup;
    s16 trailGroup;
    u8 mode;
    u8 pad_195[3];
    s32 range;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern void UpdateSceneGroupEntries(void);
extern void UpdateActiveEntries(void);
extern void UpdateSweepProjectile(void);
extern void UpdateHomingBounceProjectile(void);
extern void SpawnHitEffectOnEvent(void);
extern void PlayHitReactionSound(void);
extern void LoadUnitSharedRecords(SpawnedUnit *unit, u32 baseId, u32 kind);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);

SpawnedUnit *SpawnBounceShooterUnit(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    SpawnParams spawn;
    UnitParams params;
    EntryGroupDesc desc;

    unit = AllocEntity(spawner->ownerId, -1, 0x19c, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24(spawner, &spawn);
    InitializeUnitParameters(unit, &spawn, &params);
    params.mode = 6;
    params.flags = 0;
    params.field_4c = 2;
    SetupOwnerAndEntries(unit,
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (spawner->baseId & 0x1ff),
        ((spawner->baseId + 2) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        &params, 1, spawner->team);
    unit->drawCallback = UpdateActiveEntries;
    unit->updateCallback = UpdateSceneGroupEntries;
    unit->callback_28 = UpdateSweepProjectile;
    unit->hitCallback = UpdateHomingBounceProjectile;
    unit->callback_38 = SpawnHitEffectOnEvent;
    unit->callback_34 = PlayHitReactionSound;
    unit->records = NNSi_FndAllocFromDefaultHeap(unit->team * sizeof(TeamRecord));
    unit->mode = spawn.mode;
    unit->range = spawn.range;
    ZeroBytes0x14(&desc);
    desc.modelKey = ARCHIVE_FILE_KEY(spawner->baseId + 5);
    desc.animationKey = ARCHIVE_FILE_KEY(spawner->baseId + 6);
    desc.slotCount = 3;
    unit->effectGroup = func_ov021_020a89c8(&desc);
    desc.modelKey = ARCHIVE_FILE_KEY(spawner->baseId + 3);
    desc.animationKey = ARCHIVE_FILE_KEY(spawner->baseId + 4);
    desc.slotCount = spawner->team;
    unit->trailGroup = func_ov021_020a89c8(&desc);
    LoadUnitSharedRecords(unit, spawner->baseId, kind);
    return unit;
}
