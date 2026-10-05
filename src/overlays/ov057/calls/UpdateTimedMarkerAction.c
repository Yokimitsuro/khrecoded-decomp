#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x11];
    u8 visible;
    u8 pad_26[0x2c - 0x26];
} MarkerRequest;

typedef struct {
    u8 pad_00[0x3c];
    u32 flags;
    u8 pad_40[0x90 - 0x40];
} AnimEntry;

typedef struct {
    u8 pad_00[0x5c];
    s32 startFrame;
    s32 endFrame;
    u8 pad_64[8];
    AnimEntry *entries;
    u8 pad_70[0xc];
    s16 *groupId;
    s8 pad_80;
    s8 markerSlot;
} AnimRecord;

typedef struct {
    u8 pad_00[0x20];
} SlotEntry;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*onLand)(Actor *actor, int a, int b);
    u8 pad_1fc[0x234 - 0x1fc];
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
};

extern void func_ov052_020cffac(Actor *actor, AnimEntry *entry);
extern void func_ov052_020d1a88(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern int func_ov052_020d014c(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL func_ov052_020d02b4(Actor *actor, AnimEntry *data, int which);
extern void func_ov021_020a8ad4(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern BOOL func_ov021_020a8d3c(int groupId);
extern void func_ov021_020a8e34(int groupId, int index);
extern u16 func_ov052_020ceb9c(Actor *actor);

void UpdateTimedMarkerAction(Actor *actor)
{
    AnimRecord *record = actor->record;
    AnimEntry *entry = &record->entries[actor->animIndex];
    SlotEntry slot;
    MarkerRequest request;
    int groupId;

    func_ov052_020cffac(actor, entry);
    func_ov052_020d1a88(&slot, entry, 0, record, actor->player);
    groupId = *record->groupId;
    if (actor->frame >= record->endFrame) {
        if (record->markerSlot != -1 && func_ov021_020a8d3c(groupId)) {
            func_ov021_020a8e34(groupId, record->markerSlot);
            record->markerSlot = -1;
        }
    } else if (actor->frame >= record->startFrame && record->markerSlot == -1) {
        func_ov052_020ceb9c(actor);
        func_ov021_020a8ad4(&request);
        request.id = actor->player;
        request.visible = 1;
        request.angle = 0x8000;
        record->markerSlot = func_ov021_020a8cc0(&request, *record->groupId);
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
    if (actor->stateFlags & 4) {
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
