#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    s32 rate;
    void *target;
    u8 pad_1c[8];
    u8 mode;
    u8 loop;
    s16 priority;
    s16 index;
} TrackState;

typedef struct EffectParams {
    u8 pad_00[4];
    s16 frame;
} EffectParams;

typedef struct EffectContext {
    u8 pad_000[0x6cc];
    u8 target[0x2e8];
    u8 effectId;
    u8 pad_9b5[0x61b];
    EffectParams *params;
} EffectContext;

typedef struct GroupMember {
    u8 pad_00[0xb8];
    int frame;
} GroupMember;

typedef struct EffectOwner {
    u8 pad_00[8];
    int active;
    u8 pad_0c[0x14];
    EffectContext *context;
    u8 pad_24[0xc];
    s16 mainGroup;
    s16 subGroup;
} EffectOwner;

extern void ResetAnimationTrackState(TrackState *state);
extern int func_ov021_020a8cc0(TrackState *request, int groupId);
extern GroupMember *GetGroupMemberData(int group, int member);

void StartObjectEffects(EffectOwner *owner)
{
    EffectContext *context;
    TrackState request;

    owner->active = 1;
    context = owner->context;
    ResetAnimationTrackState(&request);
    request.id = context->effectId;
    request.loop = 2;
    request.priority = 2;
    request.mode = 0;
    request.target = context->target;
    func_ov021_020a8cc0(&request, owner->mainGroup);
    GetGroupMemberData(owner->mainGroup, 0)->frame = context->params->frame;
    ResetAnimationTrackState(&request);
    request.id = context->effectId;
    request.loop = 2;
    request.priority = 2;
    request.mode = 0;
    request.target = context->target;
    func_ov021_020a8cc0(&request, owner->subGroup);
}
