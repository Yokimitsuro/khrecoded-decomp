#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[4];
    void *user;
    u8 pad_1c[8];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x90];
} AnimEntry;

typedef struct {
    u8 pad_00[8];
    s32 soundId;
    u8 pad_0c[0x60];
    AnimEntry *entries;
    u8 pad_70[8];
    s16 *groupA;
    s16 *groupB;
    s8 slotA;
    s8 slotB;
} AnimRecord;

typedef struct {
    u8 pad_00[0x20];
} SlotEntry;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x234];
    u32 stateFlags;
    u8 pad_238[0x6cc - 0x238];
    u8 modelUser[4];
    u8 pad_6d0[0x760 - 0x6d0];
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
};

extern void func_ov052_020cffac(Actor *actor, AnimEntry *entry);
extern void func_ov052_020d1a88(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern int func_ov052_020d014c(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL func_ov052_020d02b4(Actor *actor, AnimEntry *data, int which);
extern void func_ov001_020734f8(void);
extern void func_ov001_0206e160(u32 enabled);
extern void func_ov021_020a8ad4(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void func_ov021_020af564(int a, int b);
extern void EmitSweepHitEvents(Actor *actor);

void UpdateDualMarkerAction(Actor *actor)
{
    AnimRecord *record = actor->record;
    AnimEntry *entry = &record->entries[actor->animIndex];
    SlotEntry slot;
    MarkerRequest request;
    u32 flags;

    func_ov052_020cffac(actor, entry);
    func_ov052_020d1a88(&slot, entry, 0, record, actor->player);
    EmitSweepHitEvents(actor);
    if (record->slotA == -1 && actor->frame >= 0x7000) {
        func_ov021_020a8ad4(&request);
        request.id = actor->player;
        request.layer = 2;
        request.hidden = 0;
        request.user = actor->modelUser;
        request.soundId = record->soundId;
        request.delay = 0;
        record->slotA = func_ov021_020a8cc0(&request, *record->groupA);
    }
    if (record->slotB == -1 && actor->frame >= 0x35000) {
        func_ov021_020a8ad4(&request);
        request.id = actor->player;
        request.layer = 1;
        request.angle = 0x8000;
        request.soundId = record->soundId;
        request.delay = 1;
        record->slotB = func_ov021_020a8cc0(&request, *record->groupB);
    }
    if (actor->frame == 0x37000) {
        func_ov021_020af564(3, 1);
    }
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
