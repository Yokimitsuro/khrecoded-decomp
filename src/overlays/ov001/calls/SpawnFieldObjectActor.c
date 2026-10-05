#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    u16 *spawnCounter;
    s32 recordParamB;
    u8 pad_5c[0x8];
    s16 saveIndex;
    u8 pad_66[0xa];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[0x13];
    fx32 baseHeight;
    u8 pad_94[0x18];
    fx32 topHeight;
    u8 pad_b0[0xc];
    s8 spawnedIndex;
} FieldObjectDef;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7A];
    u16 angle;
} FieldActor;

typedef struct ActorEntry {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[6];
    FieldActor actor;
} ActorEntry;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    ActorEntry *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x11];
    u16 angle;
    u16 stateFlags;
} FieldObject;

extern BOOL func_ov001_020807b4(ActorEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern BOOL ActivateEntrySubobject(ActorEntry *entry, u16 *param2, s32 param3, u32 param4);
extern void Obj_SetPosition(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ActorSlot_SetFlag8(ActorEntry *slot, BOOL enable);
extern void ActorSlot_PlaceAndLink(ActorEntry *slot, int anchor, const VecFx32 *offset);

void SpawnFieldObjectActor(FieldObject *object) {
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    ActorEntry *entry;
    FieldActor *actor;

    if (def->saveIndex >= 0) {
        if (def->spawnedIndex < 0) {
            def->spawnedIndex = object->index;
            func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape,
                                     def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle,
                                     !(object->stateFlags & 8), TRUE);
            ActivateEntrySubobject(object->entry, def->spawnCounter, def->recordParamB, 3);
            entry = object->entry;
            {
                VecFx32 offset = {0, 0, 0};
                actor = &entry->actor;
                offset.z = def->topHeight - def->baseHeight - FX32_ONE;
                Obj_SetPosition(actor, &offset);
            }
            if (!(entry->actor.flags & 0x20)) {
                actor->angle = 0;
                actor->animFlags |= 0x20;
            }
            RebindAnimTracks(&actor->animFlags, 0, 0);
            Flags16_ClearBit1(&actor->animFlags);
            if (IsObjectFlagClear(object)) {
                ActorSlot_SetFlag8(object->entry, TRUE);
                ActorSlot_PlaceAndLink(object->entry, 0, NULL);
                object->entry->flags |= 0x200;
            } else {
                ActorSlot_SetFlag8(object->entry, FALSE);
            }
            return;
        }
        (*def->spawnCounter)--;
    }
}
