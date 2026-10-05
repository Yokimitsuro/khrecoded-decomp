#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[2];
    u16 angle;
    u8 pad_14[0x10];
    s8 doubled;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x3c];
    u32 flags;
    u8 pad_40[0x90 - 0x40];
} AnimEntry;

typedef struct {
    u8 pad_00[8];
    s32 prevIndex;
    u8 pad_0c[0x50];
    s32 lowHeight;
    u8 pad_60[0xc];
    AnimEntry *entries;
    u8 pad_70[0xc];
    s16 *groupId;
    s8 highSlot;
    s8 lowSlot;
} AnimRecord;

typedef struct {
    u8 pad_00[0x18];
    u16 flags;
    u8 pad_1a[6];
} SlotEntry;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*onLand)(Actor *actor, int a, int b);
    u8 pad_1fc[0x234 - 0x1fc];
    u32 stateFlags;
    u8 pad_238[0x760 - 0x238];
    s32 height;
    u8 pad_764[4];
    s32 active;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0x9ec - 0x9b5];
    s32 slotTarget;
    u8 pad_9f0[0xa51 - 0x9f0];
    s8 animIndex;
    u8 pad_a52[0x1078 - 0xa52];
    AnimRecord *record;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(Actor *actor, int state);
};

extern int func_ov001_02072040(void);
extern void func_ov052_020cfdd4(Actor *actor, AnimEntry *entry, int arg);
extern void ApplyAnimRootMotion(Actor *actor, AnimEntry *entry);
extern void func_ov052_020d1a88(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern int ProcessTargetHitEntries(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL UpdateActionPhase(Actor *actor, AnimEntry *data, int which);
extern int func_ov052_020d03d8(Actor *actor);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void func_ov021_020a8ec8(int groupId, int index, s32 target);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern u16 GetLinkedAngleOffset(Actor *actor);

void UpdateComboTrailSlot(Actor *actor)
{
    SlotEntry slot;
    MarkerRequest request;
    AnimRecord *record;
    AnimEntry *entry;
    int mirrored;
    u32 stateFlags;

    mirrored = func_ov001_02072040();
    record = actor->record;
    entry = &record->entries[actor->animIndex];
    func_ov052_020cfdd4(actor, entry, mirrored);
    ApplyAnimRootMotion(actor, entry);
    func_ov052_020d1a88(&slot, entry, mirrored, record, actor->player);
    if (actor->animIndex > 1) {
        slot.flags |= 0x200;
    }
    if (record->lowSlot == -1) {
        if (actor->height >= record->lowHeight) {
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.pos = *func_ov052_020ceb74(actor);
            request.angle = GetLinkedAngleOffset(actor) + 0x8000;
            request.doubled = actor->animIndex;
            request.prevIndex = record->prevIndex;
            request.index = actor->animIndex;
            record->lowSlot = func_ov021_020a8cc0(&request, *record->groupId);
        }
    } else {
        func_ov021_020a8ec8(*record->groupId, record->lowSlot, actor->slotTarget);
    }
    if (ProcessTargetHitEntries(actor, entry, &slot)) {
        return;
    }
    if (UpdateActionPhase(actor, entry, mirrored)) {
        return;
    }
    if (actor->active == 0) {
        return;
    }
    stateFlags = actor->stateFlags & 4;
    if (func_ov052_020d03d8(actor)) {
        return;
    }
    if (stateFlags) {
        if (!(entry->flags & 4)) {
            actor->setState(actor, 1);
            if (actor->onLand != NULL) {
                actor->onLand(actor, 0, -1);
            }
        } else {
            actor->setState(actor, 5);
        }
    } else {
        actor->setState(actor, 4);
    }
}
