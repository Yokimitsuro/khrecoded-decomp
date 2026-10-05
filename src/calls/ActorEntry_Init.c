#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    u32 flags;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeParams;

typedef struct ShapeDesc {
    u16 flags;
    u16 group;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeDesc;

typedef struct ActorEntry {
    u8 pad_000[8];
    u16 flags;
    u8 pad_00A[2];
    s8 priority;
    u8 pad_00D[3];
    u8 object[0x194];
    u8 attributes[4];
    u8 pad_1A8[0x1c];
    s16 animSpeed;
    u8 pad_1C6[2];
    void (*draw)(struct ActorEntry *entry, BOOL useOverride);
    void (*update)(struct ActorEntry *entry, fx32 deltaTime);
} ActorEntry;

extern void ActorRegistry_RegisterSlot(ActorEntry *entry, int slot);
extern BOOL Obj_InitLinkState(void *object);
extern BOOL SetupOwnerCollisionShape(void *object, ShapeDesc *desc);
extern void ActorSlot_Draw(ActorEntry *entry, BOOL useOverride);
extern void ActorSlot_AdvanceAnimation(ActorEntry *entry, fx32 deltaTime);

void ActorEntry_Init(int slot, ActorEntry *entry, u16 group, const u8 *attributes, const ShapeParams *shape, BOOL flag20, s8 priority)
{
    ShapeDesc desc;

    if (slot != 0xffff) {
        ActorRegistry_RegisterSlot(entry, slot);
    }
    Obj_InitLinkState(entry->object);
    if (shape != NULL) {
        desc.flags = shape->flags;
        desc.group = group;
        desc.extentA = shape->extentA;
        desc.extentB = shape->extentB;
        desc.extentA = shape->extentA;
        desc.extentC = shape->extentC;
        desc.extentD = shape->extentD;
        SetupOwnerCollisionShape(entry->object, &desc);
    }
    if (attributes != NULL) {
        entry->attributes[0] = attributes[0];
        entry->attributes[1] = attributes[1];
        entry->attributes[2] = attributes[2];
        entry->attributes[3] = attributes[3];
    }
    entry->flags |= 1;
    if (flag20) {
        entry->flags |= 0x20;
    } else {
        entry->flags &= 0xffdf;
    }
    entry->animSpeed = 0x1000;
    entry->priority = priority;
    entry->draw = ActorSlot_Draw;
    entry->update = ActorSlot_AdvanceAnimation;
}
