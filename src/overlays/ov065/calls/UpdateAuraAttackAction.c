#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x90];
} AnimEntry;

typedef struct {
    u8 pad_00[0x6c];
    AnimEntry *entries;
} AnimRecord;

typedef struct {
    u8 pad_00[0x20];
} SlotEntry;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x234];
    u32 stateFlags;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[4];
    s32 active;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0xa51 - 0x9b5];
    s8 animIndex;
    u8 pad_a52[0x1078 - 0xa52];
    AnimRecord *record;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(Actor *actor, int state);
    u8 pad_10f0[8];
    void (*updateCallback)();
};

extern void func_ov052_020cffac(Actor *actor, AnimEntry *entry);
extern void func_ov052_020d1a88(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern int func_ov052_020d014c(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL func_ov052_020d02b4(Actor *actor, AnimEntry *data, int which);
extern void func_ov001_020734f8(void);
extern void func_ov001_0206e160(u32 enabled);
extern void FireMarkedGroupShot();
extern void SpawnTimedAuraMarker(AnimRecord *record, Actor *actor, s32 frame);

void UpdateAuraAttackAction(Actor *actor)
{
    AnimRecord *record = actor->record;
    AnimEntry *entry = &record->entries[actor->animIndex];
    SlotEntry slot;
    u32 flags;

    func_ov052_020cffac(actor, entry);
    func_ov052_020d1a88(&slot, entry, 0, record, actor->player);
    actor->updateCallback = FireMarkedGroupShot;
    SpawnTimedAuraMarker(record, actor, actor->frame);
    if (func_ov052_020d014c(actor, entry, &slot)) {
        return;
    }
    if (func_ov052_020d02b4(actor, entry, 0)) {
        return;
    }
    if (actor->active == 0) {
        return;
    }
    flags = actor->stateFlags & 4;
    func_ov001_020734f8();
    func_ov001_0206e160(0);
    if (flags) {
        actor->setState(actor, 5);
    } else {
        actor->setState(actor, 4);
    }
}
