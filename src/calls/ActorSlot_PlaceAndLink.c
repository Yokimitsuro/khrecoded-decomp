#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[6];
    u32 actorFlags;
    u16 nodeFlags;
    u8 pad_16[0x7a];
    u16 anchorValue;
    u8 pad_92[0x134];
    s8 warmupTimer;
} ActorSlot;

typedef struct {
    u8 pad_00[0xc];
    ActorSlot *secondaryHead;
    ActorSlot *secondaryTail;
    ActorSlot *primaryHead;
    ActorSlot *primaryTail;
} ActorRegistry;

extern int ProjectPositionDownward(void *cont, int p3, void *out);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Obj_PlaceInWorld(ActorRegistry *registry, void *actor, const VecFx32 *position);
extern int CollModel_GetEntryField14(void *model, void *key);
extern void InsertNodeByPriority(ActorSlot *slot, ActorSlot **head, ActorSlot **tail);
extern ActorRegistry *gActorRegistry;

void ActorSlot_PlaceAndLink(ActorSlot *slot, int anchor, const VecFx32 *offset)
{
    ActorRegistry *registry = gActorRegistry;
    VecFx32 position;

    if (anchor != 0 && ProjectPositionDownward(registry, anchor, &position)) {
        if (offset != NULL) {
            func_01ff9e0c(&position, offset, &position);
        }
        Obj_PlaceInWorld(registry, &slot->actorFlags, &position);
        {
            int value = CollModel_GetEntryField14(registry, (void *)anchor);
            if ((slot->actorFlags & 0x20) == 0) {
                slot->anchorValue = value;
                slot->nodeFlags |= 0x20;
            }
        }
    } else {
        Obj_PlaceInWorld(registry, &slot->actorFlags, offset);
    }
    slot->flags |= 0x10a;
    slot->warmupTimer = 0;
    if (slot->flags & 0x20) {
        InsertNodeByPriority(slot, &gActorRegistry->secondaryHead, &gActorRegistry->secondaryTail);
    } else {
        InsertNodeByPriority(slot, &gActorRegistry->primaryHead, &gActorRegistry->primaryTail);
    }
}
