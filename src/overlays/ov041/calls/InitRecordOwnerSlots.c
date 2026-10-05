#include "nitro/types.h"

typedef struct {
    u32 state;
    u8 pad_04[0x34];
} RecordEntry;

typedef struct {
    u8 pad_00[0x10];
    void *parent;
} ActorSlot;

typedef struct {
    RecordEntry entries[0x80];
    ActorSlot slot;
} RecordOwner;

extern void func_0203670c(ActorSlot *slot);
extern void ActorSlot_LinkAsRoot(ActorSlot *slot);
extern void LoadSharedRecordField(RecordOwner *owner);

void InitRecordOwnerSlots(RecordOwner *owner) {
    int i;

    func_0203670c(&owner->slot);
    if (owner->slot.parent == NULL) {
        ActorSlot_LinkAsRoot(&owner->slot);
    }
    LoadSharedRecordField(owner);
    for (i = 0; i < 0x80; i++) {
        owner->entries[i].state = 2;
    }
}
