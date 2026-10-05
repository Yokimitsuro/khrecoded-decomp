#include "nitro/types.h"

typedef struct ActorRecord {
    u8 pad_00[0x10];
    void *owner;
} ActorRecord;

typedef struct ActorLink {
    u8 pad_00[0x80];
    u8 recordId;
} ActorLink;

typedef struct ActorTargeting {
    u32 unk_00;
    ActorLink *link;
    u8 pad_08[8];
    void *owner;
    u8 pad_14[0xb0];
    int mode;
} ActorTargeting;

typedef struct FieldActor FieldActor;

struct FieldActor {
    u8 pad_000[0x21c];
    u32 (*getState)(FieldActor *actor);
    u8 pad_220[0x14];
    u32 flags;
    u8 pad_238[0x3c];
    ActorTargeting targeting;
};

typedef struct TargetSlot {
    u8 pad_00[0xc];
    void *owner;
} TargetSlot;

extern void AddSessionCounter(int state, int flags);
extern ActorRecord *GetActorRecord(ActorTargeting *targeting, u8 recordId);
extern BOOL func_ov001_020681e8(ActorRecord *record, int mode);

static inline u32 GetActorState(FieldActor *actor)
{
    return actor->getState != NULL ? actor->getState(actor) : 0;
}

void UpdateActorTargetLink(FieldActor *actor, TargetSlot *slot)
{
    ActorTargeting *targeting = &actor->targeting;
    BOOL active = TRUE;
    ActorRecord *record;

    if (!(actor->flags & 4) && !(GetActorState(actor) & 8)) {
        active = FALSE;
    }
    if (active) {
        AddSessionCounter(0xe, 1);
    } else {
        AddSessionCounter(0xf, 1);
    }
    if (targeting->mode == 2 && targeting->link != NULL && targeting->owner == NULL) {
        record = GetActorRecord(targeting, targeting->link->recordId);
        if (record != NULL && func_ov001_020681e8(record, 1) && slot->owner == NULL) {
            slot->owner = record->owner;
        }
    }
}
