#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimSlot {
    u8 pad_00[4];
    s16 animId;
    u8 pad_06[2];
    u32 param;
    char name[0x20];
} AnimSlot;

typedef struct ActorNode {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
    u8 pad_82[0x26];
    VecFx32 position;
} ActorNode;

typedef struct OffsetEntry {
    VecFx32 offset;
    u8 pad_0c[0x14];
    s32 weight;
    u8 pad_24[4];
} OffsetEntry;

typedef struct Actor {
    u8 pad_000[0xd0];
    AnimSlot slots[6][5];
    u8 pad_5f8[0x108];
    OffsetEntry offsets[7];
    u8 pad_818[0x28];
    VecFx32 target;
    u8 pad_84c[0xc];
    s32 moving;
    s32 pendingAnim;
    u8 pad_860[0x4b8];
    ActorNode **model;
    u8 pad_d1c[0x1d8];
    u32 flags;
    u8 pad_ef8[4];
    u32 angle;
    int entryIndex;
} Actor;

extern const VecFx32 data_0205344c;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void Actor_SetVelocity(Actor *actor, const VecFx32 *velocity);
extern void ActivateFreeSlotEntry(Actor *actor, int a1, int animId, int a3, int a4, int a5);
extern void SetActorAnimSlot(Actor *actor, const char *name, s16 animId, int slot, u32 param);
extern u32 GetBoundedEntryField(int index);
extern u8 *GetActorFieldBySessionMode(u32 entry);
extern void CommitPendingAnimationSwap(u16 *state);

static inline void SetNodeAngle(ActorNode *node, u32 angle)
{
    if (!(node->flags & 0x20)) {
        node->angle = angle;
        node->animFlags |= 0x20;
    }
}

void Actor_RestoreAnimState(Actor *actor, BOOL keepParams)
{
    VecFx32 delta;
    VecFx32 zero;
    ActorNode *node;
    u16 *state;
    AnimSlot *slot;
    OffsetEntry *entry;
    int layer;
    int depth;
    int i;

    if (actor->flags == 0) {
        return;
    }
    if (actor->moving) {
        delta = (*actor->model)->position;
        VEC_Subtract(&actor->target, &delta, &delta);
        if (VEC_Mag(&delta) > 0) {
            Actor_SetVelocity(actor, &delta);
            SetNodeAngle(*actor->model, actor->angle);
        }
        if (actor->pendingAnim != -1) {
            ActivateFreeSlotEntry(actor, 0, actor->pendingAnim, 0, 0, 0);
        }
        actor->moving = 0;
    }
    if (actor->flags & 0x200) {
        for (layer = 0; layer < 5; layer++) {
            for (depth = 5; depth >= 0; depth--) {
                slot = &actor->slots[depth][layer];
                if (slot->animId != -1 || slot->name[0] != '\0') {
                    SetActorAnimSlot(actor, slot->name, slot->animId, layer, keepParams ? 0 : slot->param);
                    break;
                }
            }
        }
    }
    if (actor->flags & 0x400) {
        zero = data_0205344c;
        for (i = 0; i < 7; i++) {
            entry = &actor->offsets[i];
            if (!keepParams) {
                entry->offset = zero;
            }
            entry->weight = 0;
        }
    }
    if (keepParams) {
        if (actor->flags & 0x4000) {
            state = (u16 *)(GetActorFieldBySessionMode(GetBoundedEntryField(actor->entryIndex)) + 8);
        } else {
            node = *actor->model;
            state = &node->animFlags;
            SetNodeAngle(node, actor->angle);
        }
        if (*state & 4) {
            CommitPendingAnimationSwap(state);
        }
    }
}
