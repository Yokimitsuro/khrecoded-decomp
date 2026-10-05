#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    s32 unk_54;
    s32 turnInterval;
    s32 lifetime;
} SpawnParams;

typedef struct {
    s32 mode;
    s32 unk_04;
    u8 pad_08[0x44];
    s32 unk_4c;
    u8 pad_50[0x10];
} UnitSetup;

typedef struct {
    u32 fileIndex;
    s32 ownerId;
    u8 pad_08[0xC];
    s32 unk_14;
} Spawner;

typedef void (*EntityCallback)(void);

typedef struct {
    u8 pad_000[0x1c];
    EntityCallback drawCallback;
    EntityCallback releaseCallback;
    u8 pad_024[8];
    EntityCallback updateCallback;
    u8 pad_030[8];
    EntityCallback hitCallback;
    u8 pad_03c[2];
    u8 unk_3e;
    u8 pad_03f[0x188 - 0x3f];
    u16 unk_188;
    u8 pad_18a[2];
    u8 effect[0x1b0 - 0x18c];
    u8 phase;
    u8 pad_1b1[7];
    s32 lifetime;
    s32 unk_1bc;
    s32 turnInterval;
    s32 unk_1c4;
    u8 pad_1c8[4];
} SpiralProjectile;

extern SpiralProjectile *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters(SpiralProjectile *entity, SpawnParams *params, UnitSetup *setup);
extern u32 func_ov001_0206dba0(int index);
extern void SetupOwnerAndEntries(SpiralProjectile *entity, u32 first, u32 second, UnitSetup *setup, int x, int y);
extern void func_ov030_020bcb3c(void);
extern void UpdateCarriedLauncher(void);
extern void UpdateSpiralProjectile(void);
extern void OnUnitHitEvent(void);
extern void AllocModelSlots(u8 *effect, u32 fileIndex, int count, u32 kind);
extern void LoadUnitSharedRecords(SpiralProjectile *entity, u32 fileIndex, u32 kind);

SpiralProjectile *SpawnSpiralProjectile(Spawner *spawner, u16 value, u32 kind)
{
    SpiralProjectile *entity;
    SpawnParams params;
    UnitSetup setup;

    entity = AllocEntity(spawner->ownerId, -1, sizeof(SpiralProjectile), kind);
    entity->unk_3e = spawner->unk_14;
    entity->unk_188 = value;
    CopyWordArray24(spawner, &params);
    InitializeUnitParameters(entity, &params, &setup);
    setup.mode = 6;
    setup.unk_04 = 0;
    setup.unk_4c = -1;
    SetupOwnerAndEntries(entity,
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (spawner->fileIndex & 0x1ff),
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | ((spawner->fileIndex + 2) & 0x1ff),
        &setup, 1, 8);
    entity->releaseCallback = func_ov030_020bcb3c;
    entity->drawCallback = UpdateCarriedLauncher;
    entity->updateCallback = UpdateSpiralProjectile;
    entity->hitCallback = OnUnitHitEvent;
    entity->phase = 0;
    entity->unk_1c4 = 0;
    entity->lifetime = params.lifetime;
    entity->turnInterval = params.turnInterval;
    entity->unk_1bc = params.unk_54;
    AllocModelSlots(entity->effect, spawner->fileIndex, 6, kind);
    LoadUnitSharedRecords(entity, spawner->fileIndex, kind);
    return entity;
}

