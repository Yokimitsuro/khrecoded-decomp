#include "nitro/types.h"

typedef struct UnitSetup {
    u8 pad00[4];
    int unk04;
    u8 pad08[0x44];
    int unk4c;
    u8 pad50[0x10];
} UnitSetup;

typedef struct Spawner {
    u32 entryId;
    s32 ownerId;
    u8 pad08[0xc];
    s32 unk14;
} Spawner;

typedef struct SpawnedEntity {
    u8 pad000[0x1c];
    void *updateCallback;
    void *drawCallback;
    u8 pad024[4];
    void *callback28;
    u8 pad02c[8];
    void *callback34;
    u8 pad038[6];
    u8 unk3e;
    u8 pad03f[0x149];
    u16 unk188;
    u8 pad18a[2];
} SpawnedEntity;

extern SpawnedEntity *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, u32 *params);
extern void InitializeUnitParameters(SpawnedEntity *entity, u32 *params, UnitSetup *unit);
extern u32 func_ov001_0206dba0(int index);
extern void SetupOwnerAndEntries(SpawnedEntity *entity, u32 first, u32 second, UnitSetup *unit, int mode, int value);
extern void UpdateGroupAngles(void);
extern void UpdateSceneGroupEntries(void);
extern void UpdateUnitAttackSweep(void);
extern void PlayHitReactionSound(void);
extern void LoadUnitSharedRecords(SpawnedEntity *entity, u32 entryId, u32 kind);

#define MakeEntryKey(entryId) (((entryId) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000))

SpawnedEntity *SpawnPairedEntryUnit(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedEntity *entity;
    u32 params[24];
    UnitSetup unit;

    entity = AllocEntity(spawner->ownerId, -1, sizeof(SpawnedEntity), kind);
    entity->unk3e = spawner->unk14;
    entity->unk188 = value;
    CopyWordArray24(spawner, params);
    InitializeUnitParameters(entity, params, &unit);
    unit.unk04 = 0;
    unit.unk4c = 2;
    SetupOwnerAndEntries(entity,
        MakeEntryKey(spawner->entryId),
        MakeEntryKey(spawner->entryId + 2),
        &unit, 1, spawner->unk14);
    entity->drawCallback = UpdateGroupAngles;
    entity->updateCallback = UpdateSceneGroupEntries;
    entity->callback28 = UpdateUnitAttackSweep;
    entity->callback34 = PlayHitReactionSound;
    LoadUnitSharedRecords(entity, spawner->entryId, kind);
    return entity;
}
