#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    u32 flags;
    u8 pad_40[0x90 - 0x40];
} AnimEntry;

typedef struct {
    u8 pad_00[0x6c];
    AnimEntry *entries;
} AnimRecord;

typedef struct {
    u8 data[0x20];
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
    u8 pad_76c[0x9ac - 0x76c];
    u64 moveFlags;
    u8 player;
    u8 pad_9b5[0xa51 - 0x9b5];
    s8 animIndex;
    u8 pad_a52[0x1078 - 0xa52];
    AnimRecord *record;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(Actor *actor, int state);
    u8 pad_10f0[8];
    void *stateHandler;
};

extern void func_ov052_020cfdd4(Actor *actor, AnimEntry *entry, int arg);
extern void ApplyAnimRootMotion(Actor *actor, AnimEntry *entry);
extern void func_ov052_020d1a88(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern int ProcessTargetHitEntries(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL UpdateActionPhase(Actor *actor, AnimEntry *data, int which);
extern int HandlePendingCommand(Actor *actor);
extern void FireMarkedLinkedShot(void);

void UpdateAirborneActionState(Actor *actor)
{
    SlotEntry slot;
    AnimRecord *record;
    AnimEntry *entry;
    u32 stateFlags;

    record = actor->record;
    entry = &record->entries[actor->animIndex];
    func_ov052_020cfdd4(actor, entry, 0);
    ApplyAnimRootMotion(actor, entry);
    func_ov052_020d1a88(&slot, entry, 0, record, actor->player);
    actor->stateHandler = FireMarkedLinkedShot;
    if ((actor->moveFlags & 0x40) == 0) {
        if (actor->height >= 0x25000) {
            actor->moveFlags |= 0x40;
        }
    } else if (actor->height >= 0xf000 && actor->height < 0x25000) {
        actor->moveFlags &= ~0x40;
    }
    if (ProcessTargetHitEntries(actor, entry, &slot)) {
        return;
    }
    if (UpdateActionPhase(actor, entry, 0)) {
        return;
    }
    if (actor->active == 0) {
        return;
    }
    stateFlags = actor->stateFlags & 4;
    if (HandlePendingCommand(actor)) {
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
