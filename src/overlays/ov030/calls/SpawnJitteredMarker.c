#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_000[0x9b4];
    u8 markerId;
} SceneActor;

typedef struct {
    u32 flags;
    u8 pad_04[8];
    VecFx32 pos;
} HitEvent;

typedef struct {
    u8 pad_00[0x74];
    s16 *groupId;
} MarkerOwner;

typedef struct {
    u8 pad_00[4];
    MarkerOwner *owner;
} MarkerContext;

extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int nextRandom12(void);
extern fx32 FX_Mul(fx32 a, fx32 b);

void SpawnJitteredMarker(SceneActor *actor, HitEvent *event, MarkerContext *context)
{
    MarkerRequest request;
    VecFx32 pos;
    MarkerOwner *owner = context->owner;

    if ((event->flags & 1) || (event->flags & 0x20) || owner->groupId == NULL) {
        return;
    }
    ResetAnimationTrackState(&request);
    request.id = actor->markerId;
    request.unk_25 = 0;
    request.unk_24 = 0;
    request.index = -1;
    request.prevIndex = request.index;
    pos = event->pos;
    pos.x += FX_Mul(nextRandom12() - 0x800, 0x4cd);
    pos.y += FX_Mul(nextRandom12() - 0x800, 0x4cd);
    pos.z += FX_Mul(nextRandom12() - 0x800, 0x4cd);
    request.pos = pos;
    func_ov021_020a8cc0(&request, *owner->groupId);
}
