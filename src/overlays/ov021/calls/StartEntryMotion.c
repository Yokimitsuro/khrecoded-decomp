#include "nitro/types.h"

typedef struct {
    u8 entryIndex;
    u8 pad_01[0x17];
    void *source;
    u8 pad_1c[8];
    u8 unk_24;
    u8 mode;
    u16 kind;
    u16 ownerId;
    u16 motion;
} SlotRequest;

typedef struct MotionEntry {
    u8 pad_000[0x1f0];
    void (*playMotion)(struct MotionEntry *entry, u32 ownerId, int motion, int flags);
    u8 pad_1f4[0x4d8];
    u8 source[0x2e8];
    u8 index;
    u8 pad_9b5[3];
    BOOL busy;
    u8 pad_9bc[0x614];
    s16 *timing;
} MotionEntry;

typedef struct {
    u8 pad_00[0x14];
    int entryIndex;
} MotionOwner;

typedef struct {
    u8 pad_00[8];
    u32 id;
    u8 pad_0c[0x48];
    int startMotion;
    int idleMotion;
    u8 pad_5c[0x1c];
    s16 *group;
    void *script;
    s8 slot;
    s8 subSlot;
} MotionActor;

extern MotionEntry *GetBoundedEntryField(int index);
extern void ResetAnimationTrackState(SlotRequest *request);
extern int func_ov021_020a8cc0(SlotRequest *request, int groupId);
extern u8 *GetGroupMemberData(int groupId, int index);
extern void SpawnTimedAuraMarker(MotionActor *actor, MotionEntry *entry, int flags);

static inline void PlayEntryMotion(MotionEntry *entry, MotionActor *actor, int motion) {
    if (motion >= 0) {
        u32 ownerId = actor->id;
        void (*play)(MotionEntry *, u32, int, int) = entry->playMotion;
        if (play != NULL) {
            play(entry, ownerId, motion, 0);
        }
    }
}

void StartEntryMotion(MotionOwner *owner, MotionActor *actor) {
    MotionEntry *entry = GetBoundedEntryField(owner->entryIndex);
    SlotRequest request;
    actor->slot = -1;
    actor->subSlot = -1;
    if (actor->group != NULL) {
        ResetAnimationTrackState(&request);
        request.entryIndex = entry->index;
        request.mode = 2;
        request.kind = 6;
        request.unk_24 = 0;
        request.source = entry->source;
        if (actor->startMotion >= 0) {
            request.ownerId = actor->id;
            request.motion = actor->startMotion;
        }
        actor->slot = func_ov021_020a8cc0(&request, *actor->group);
        if (actor->slot >= 0) {
            *(int *)(GetGroupMemberData(*actor->group, actor->slot) + 0xb8) = entry->timing[2];
        }
    } else {
        PlayEntryMotion(entry, actor, actor->startMotion);
    }
    if (!entry->busy) {
        if (actor->script != NULL) {
            SpawnTimedAuraMarker(actor, entry, 0);
        } else {
            PlayEntryMotion(entry, actor, actor->idleMotion);
        }
    }
}
