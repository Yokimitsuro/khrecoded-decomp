#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 words[4];
} ParamBlock16;

typedef struct {
    u32 words[8];
} ParamBlock32;

typedef struct {
    u32 words[25];
} ExtraData;

typedef union {
    VecFx32 anchor;
    ExtraData data;
} SpawnExtra;

typedef struct {
    VecFx32 position;
    u32 flags;
    u8 enabled : 1;
    u8 drawMode : 3;
    u8 state : 4;
    s8 weight;
    s16 facing;
    u32 carryState : 4;
    u32 hitWeight : 8;
    u32 unk_14_12 : 20;
    s32 linkValue;
    ParamBlock16 motion;
    ParamBlock16 steering;
    int soundId;
    ParamBlock32 physics;
    SpawnExtra extra;
} SpawnEntry;

typedef struct {
    u8 pad_00[0xc4];
    SpawnEntry *entries;
} FieldOwner;

typedef struct {
    u8 pad_00[4];
    FieldOwner *owner;
    u8 pad_08[0x33 - 0x08];
    u8 spawnIndex;
    u8 pad_34[0x38 - 0x34];
    VecFx32 position;
    u8 pad_44[0x47 - 0x44];
    s8 carryState;
    ParamBlock16 motion;
    ParamBlock16 steering;
    u8 pad_68[0x70 - 0x68];
    u16 drawLow : 9;
    u16 drawMode : 3;
    u16 drawHigh : 4;
    s16 facing;
    u8 pad_74[0x76 - 0x74];
    s8 hitWeight;
    u8 pad_77[0xbd - 0x77];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 unk_BE_low : 4;
    u8 state : 4;
    s8 weight;
    u32 flags;
    s32 linkValue;
    int soundId;
    ParamBlock32 physics;
    union {
        VecFx32 anchor;
        ExtraData *data;
    } extra;
} FieldObject;

void ApplyFieldObjectSpawnEntry(FieldObject *obj)
{
    SpawnEntry *entry = &obj->owner->entries[obj->spawnIndex];

    if (!entry->enabled) {
        return;
    }
    obj->position = entry->position;
    obj->drawMode = entry->drawMode;
    obj->state = entry->state;
    obj->weight = entry->weight;
    obj->hitWeight = entry->hitWeight;
    obj->flags = entry->flags;
    obj->soundId = entry->soundId;
    obj->carryState = entry->carryState;
    obj->physics = entry->physics;
    obj->facing = entry->facing;
    if (obj->phase >= 5) {
        *obj->extra.data = entry->extra.data;
    } else {
        obj->extra.anchor = entry->extra.anchor;
    }
    if (entry->state == 6) {
        return;
    }
    if (entry->flags & 0x20) {
        obj->linkValue = entry->linkValue;
    }
    if (obj->flags & 0x40) {
        obj->motion = entry->motion;
    }
    if (obj->flags & 0x8000) {
        obj->steering = entry->steering;
    }
}
