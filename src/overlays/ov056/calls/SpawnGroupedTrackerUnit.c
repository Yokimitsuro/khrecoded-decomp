#include "nitro/types.h"

#define ARCHIVE_FILE_KEY(id) (0x80000000 | (((func_ov001_0206dba0(0) + 0x8000) & 0xFFFFFC) << 7) | ((id) & 0x1ff))

typedef struct {
    s32 statA;
    s32 statB;
    u8 pad_08[4];
    s32 range;
    u8 pad_10[8];
    s32 speed;
    u8 pad_1c[0x14];
    s32 statC;
    s32 statD;
    u8 pad_38[0xc];
    s32 delay;
    u8 pad_48[0x18];
} SpawnParams;

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
    u8 pad_000[0x1c];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[0x1a];
    u8 team;
    u8 pad_03f[0x178 - 0x3f];
    s32 statA;
    s32 statB;
    s32 statC;
    s32 statD;
    u16 value;
    u8 pad_18a[2];
    s32 range;
    s32 speed;
    s32 delay;
    s16 groupId;
    u8 pad_19a[0x12];
    s32 ownerId;
    u32 progress : 16;
    u32 stage : 16;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24(Spawner *spawner, SpawnParams *params);
extern s32 func_ov001_0206dba0(s32 arg);
extern void UpdateDelayedBlastEffect(void);
extern void UpdateGroupAngles(void);
extern void LoadUnitSharedRecords(SpawnedUnit *unit, u32 baseId, u32 kind);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);

SpawnedUnit *SpawnGroupedTrackerUnit(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    EntryGroupDesc desc;
    SpawnParams spawn;

    unit = AllocEntity(spawner->ownerId, -1, 0x1b4, kind);
    unit->team = spawner->team;
    unit->value = value;
    unit->ownerId = spawner->ownerId;
    unit->progress = 0;
    unit->stage = 0;
    CopyWordArray24(spawner, &spawn);
    unit->statA = spawn.statA;
    unit->statB = spawn.statB;
    unit->statD = spawn.statD;
    unit->statC = spawn.statC;
    unit->range = spawn.range;
    unit->speed = spawn.speed;
    unit->delay = spawn.delay;
    unit->updateCallback = UpdateDelayedBlastEffect;
    unit->drawCallback = UpdateGroupAngles;
    LoadUnitSharedRecords(unit, spawner->baseId, kind);
    ZeroBytes0x14(&desc);
    desc.modelKey = ARCHIVE_FILE_KEY(spawner->baseId + 3);
    desc.animationKey = ARCHIVE_FILE_KEY(spawner->baseId + 4);
    desc.slotCount = 8;
    unit->groupId = func_ov021_020a89c8(&desc);
    return unit;
}
