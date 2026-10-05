#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4c];
    VecFx32 offset;
} ChildLayout;

typedef struct {
    u8 pad_00[0x10];
    u8 base[0xa8];
    VecFx32 position;
} ChildObject;

typedef struct {
    void *owner;
    ChildObject *object;
    int layoutIndex;
    VecFx32 delta;
} ChildSlot;

typedef struct {
    u8 pad_00[0xb8];
    VecFx32 position;
} OwnerEntry;

typedef struct {
    u8 pad_00[0xc];
    OwnerEntry *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x23];
    ChildLayout *layouts;
    u8 pad_60[0x8];
    ChildSlot children[24];
} ChildOwner;

typedef struct {
    u32 flags;
    u8 node[0x20];
    u32 drawFlags;
} FieldActor;

extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void func_01ffb12c(void *node);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void DrawChildSpawner(ChildOwner *owner)
{
    FieldActor *actor = ActorRegistry_GetEntityByIndex(owner->actorId);
    VecFx32 base;
    VecFx32 position;
    VecFx32 previous;
    int i;

    actor->drawFlags |= 1;
    if (!(actor->flags & 0x20)) {
        func_01ffb12c(actor->node);
    }
    actor->drawFlags &= ~1;
    base = owner->entry->position;
    for (i = 0; i < 24; i++) {
        ChildSlot *slot = &owner->children[i];

        position = owner->layouts[slot->layoutIndex].offset;
        VEC_Add(&position, &base, &position);
        previous = slot->object->position;
        Obj_SetPosition(slot->object->base, &position);
        VEC_Subtract(&position, &previous, &slot->delta);
    }
}
