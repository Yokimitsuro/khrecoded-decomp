#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorModel {
    u8 pad_000[0x370];
    u8 heldResource[4];
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x894];
    ActorModel model;
    u8 pad_c08[0xef4 - 0xc08];
    u32 flags;
    u8 pad_ef8[8];
    s32 partyIndex;
} Actor;

typedef struct PartyEntry {
    u8 pad_000[0x6ac];
    VecFx32 heldOffset;
} PartyEntry;

extern const VecFx32 data_0205344c;

extern s32 func_ov001_02063a38(void);
extern void ReleaseResourceAndDetach(u8 *object);
extern PartyEntry *GetBoundedEntryField(int index);

void Actor_ReleaseHeldResource(Actor *actor)
{
    ActorModel *model = &actor->model;

    if (func_ov001_02063a38() == 7) {
        return;
    }
    ReleaseResourceAndDetach(model->heldResource);
    if (actor->partyIndex < 3) {
        GetBoundedEntryField(actor->partyIndex)->heldOffset = data_0205344c;
    }
    actor->flags &= ~0x800;
}
