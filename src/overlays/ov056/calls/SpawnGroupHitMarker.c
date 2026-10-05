#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0x14];
    u8 doubled;
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
    u8 pad_04[4];
    s32 kind;
    VecFx32 pos;
} HitEvent;

typedef struct {
    u8 pad_00[0xd8];
    s16 count;
} GroupMember;

typedef struct {
    u8 pad_00[8];
    s32 prevIndex;
    u8 pad_0c[0x44];
    s32 index;
    u8 pad_54[0x20];
    s16 *groupId;
} MarkerOwner;

typedef struct {
    u8 pad_00[4];
    MarkerOwner *owner;
} MarkerContext;

extern GroupMember *func_ov021_020a8f0c(int groupId, int index);
extern void func_ov021_020a8ad4(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int nextRandom12(void);
extern fx32 FX_Mul(fx32 a, fx32 b);

void SpawnGroupHitMarker(SceneActor *actor, HitEvent *event, MarkerContext *context)
{
    MarkerRequest request;
    VecFx32 pos;
    GroupMember *member;
    MarkerOwner *owner = context->owner;

    if ((event->flags & 1) || (event->flags & 0x20) || event->kind == 1 || owner->groupId == NULL) {
        return;
    }
    member = func_ov021_020a8f0c(*owner->groupId, 0);
    func_ov021_020a8ad4(&request);
    request.id = actor->markerId;
    request.unk_25 = 0;
    request.doubled = 0;
    if (member->count > 1 && (event->flags & 2)) {
        request.doubled = 1;
    }
    if (owner->index >= 0) {
        request.prevIndex = owner->prevIndex;
        request.index = owner->index;
    }
    pos = event->pos;
    pos.x += FX_Mul(nextRandom12() - 0x800, 0x4cd);
    pos.y += FX_Mul(nextRandom12() - 0x800, 0x4cd);
    pos.z += FX_Mul(nextRandom12() - 0x800, 0x4cd);
    request.pos = pos;
    func_ov021_020a8cc0(&request, *owner->groupId);
}
