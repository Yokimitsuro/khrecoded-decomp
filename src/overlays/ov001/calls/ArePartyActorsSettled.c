#include "nitro/types.h"

typedef struct PartyActor PartyActor;

struct PartyActor {
    u8 pad_000[0x21c];
    u32 (*getState)(PartyActor *actor);
};

typedef struct PartyEntry {
    u32 unk_00;
    PartyActor *actor;
    u8 pad_08[0x20];
} PartyEntry;

typedef struct PartyState {
    u32 unk_00;
    PartyEntry entries[3];
    u8 pad_7C[0];
    int count;
} PartyState;

extern PartyState *data_ov001_020a04bc;
extern BOOL func_ov021_020a8c40(int actorId);

static inline u32 GetActorState(PartyActor *actor)
{
    return actor->getState != NULL ? actor->getState(actor) : 0;
}

BOOL ArePartyActorsSettled(void)
{
    PartyState *party = data_ov001_020a04bc;
    BOOL settled = TRUE;
    PartyEntry *entry;
    int i;

    if (party == NULL) {
        return settled;
    }
    for (i = 0; i < party->count; i++) {
        entry = &data_ov001_020a04bc->entries[i];
        if (entry->actor != NULL) {
            if (!(GetActorState(entry->actor) & 1)) {
                settled = FALSE;
                break;
            }
            if (!(GetActorState(entry->actor) & 2) && !func_ov021_020a8c40(i)) {
                settled = FALSE;
                break;
            }
        }
    }
    return settled;
}
