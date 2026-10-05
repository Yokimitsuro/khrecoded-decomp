#include "nitro/types.h"

typedef struct ReactEntry {
    u8 pad_000[0x1f8];
    void (*setMotion)(struct ReactEntry *entry, int motion, int frame);
    void (*setPose)(struct ReactEntry *entry, int pose);
    u8 pad_200[0x34];
    u32 traits;
    u8 pad_238[0x774];
    u64 stateFlags;
    u8 index;
    u8 pad_9b5[0x43];
    s32 reactTimer;
} ReactEntry;

typedef struct {
    u8 pad_00[0x14];
    int entryIndex;
} ReactOwner;

typedef struct {
    u8 pad_00[0x3d];
    s8 kind;
} ReactSource;

typedef struct {
    u8 pad_00[0x50];
    ReactSource *source;
} ReactActor;

extern ReactEntry *GetBoundedEntryField(int index);
extern int MapKindToSlot(int kind);
extern void *SelectFallStateHandler(ReactEntry *entry, int *state);
extern void RefreshLockTarget(ReactEntry *entry);
extern void UpdateFacingTowardTarget(ReactEntry *entry, int flag);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void UpdateGrabHoldState(void);

void *BeginEntryReaction(ReactOwner *owner, ReactActor *actor, int *state) {
    ReactEntry *entry = GetBoundedEntryField(owner->entryIndex);
    u32 heavy = entry->traits & 4;
    int slot = MapKindToSlot(actor->source->kind);
    int motion;
    if (slot == 8) {
        void *next = SelectFallStateHandler(entry, state);
        if (next != NULL) {
            return next;
        }
        RefreshLockTarget(entry);
    }
    switch (slot) {
    default:
        motion = 0x1f;
        if (heavy == 0) {
            motion = 0x20;
        }
        break;
    case 2:
        motion = 0x21;
        break;
    case 4:
        motion = 0x22;
        break;
    case 5:
        motion = 0x23;
        break;
    case 6:
        motion = 0x24;
        break;
    case 7:
        motion = 0x25;
        break;
    case 8:
        motion = 0x26;
        break;
    }
    if (entry->setMotion != NULL) {
        entry->setMotion(entry, motion, -1);
    }
    if (entry->setPose != NULL) {
        entry->setPose(entry, 0);
    }
    UpdateFacingTowardTarget(entry, 0);
    entry->stateFlags |= 0x40;
    *state = 0x1a;
    if (IsPlayerEntryFlagSet(entry->index, 0x15) && actor->source->kind == 3) {
        entry->reactTimer = 0x3000;
    }
    return UpdateGrabHoldState;
}
