#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PartyEntry {
    u8 pad_000[0x6ac];
    VecFx32 offset;
} PartyEntry;

typedef struct FieldActor {
    u8 pad_000[0x894];
    u8 anchor[0x66c];
    int partyIndex;
} FieldActor;

extern void ActorAnim_AdvanceAndGetRootDelta(VecFx32 *out, void *anchor);
extern int func_ov001_02063a38(void);
extern PartyEntry *GetBoundedEntryField(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Actor_FireExpiredTrackCues(FieldActor *actor);

void AlignPartyLeaderToActor(FieldActor *actor)
{
    VecFx32 position;
    VecFx32 anchor;
    PartyEntry *entry;

    ActorAnim_AdvanceAndGetRootDelta(&anchor, actor->anchor);
    position = anchor;
    if (func_ov001_02063a38() == 7) {
        return;
    }
    if (actor->partyIndex < 3) {
        entry = GetBoundedEntryField(actor->partyIndex);
        VEC_Subtract(&entry->offset, &position, &entry->offset);
    }
    Actor_FireExpiredTrackCues(actor);
}
