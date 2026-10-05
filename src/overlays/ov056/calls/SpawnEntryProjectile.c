#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct EntryInfo EntryInfo;
typedef void (*EntrySpawnCallback)(EntryInfo *info, s32 value, s32 arg2, s32 arg3);

struct EntryInfo {
    u8 pad_00[0x94];
    u16 facing;
    u8 pad_96[0xbc - 0x96];
    VecFx32 position;
    u8 pad_c8[0x1f0 - 0xc8];
    EntrySpawnCallback onSpawn;
    s32 value;
};

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
    s16 value;
} SpawnUnit;

extern s16 data_02053580[];
extern EntryInfo *GetBoundedEntryField(int index);
extern void ZeroBytes0x40(SpawnDesc *desc);
extern int TryConsumeLimitedUse(SpawnUnit *unit, SpawnDesc *desc);

void SpawnEntryProjectile(SpawnUnit *unit, void *arg, SpawnRequest *request)
{
    VecFx32 origin;
    SpawnDesc desc;
    EntryInfo *info;
    u16 angle;
    u16 facing;
    int index;
    EntrySpawnCallback onSpawn;
    s32 value;

    info = GetBoundedEntryField(unit->entryIndex);
    unit->flags = 0;
    angle = info->facing - 0x8000;
    facing = angle + 0x8000;
    origin = info->position;
    ZeroBytes0x40(&desc);
    desc.position = origin;
    index = facing >> 4;
    desc.direction.x = data_02053580[index];
    desc.direction.y = 0;
    desc.direction.z = data_02053580[(0x400 - index) & 0xfff];
    desc.unk_2c = 0;
    desc.count = 0;
    desc.paramA = unit->paramA;
    desc.paramB = unit->paramB;
    desc.paramC = unit->paramC;
    desc.kind = request->kind;
    desc.subKind = request->subKind;
    desc.power = request->power;
    if (TryConsumeLimitedUse(unit, &desc)) {
        value = unit->value;
        onSpawn = info->onSpawn;
        if (onSpawn != NULL) {
            onSpawn(info, value, 0, 0);
        }
        unit->spawnCount++;
    }
}
