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
    u8 pad_00[2];
    s16 state;
    u8 pad_04[0xb4];
    int frame;
} GroupMember;

typedef struct EffectOwner {
    u8 pad_00[8];
    int active;
    u8 pad_0c[0x14];
    EffectContext *context;
    u8 pad_24[0xc];
    s16 groups[2];
} EffectOwner;

extern void ResetAnimationTrackState(TrackState *state);
extern int func_ov021_020a8cc0(TrackState *request, int groupId);
extern void StopAndClearSoundEmitter(int group, int member);
extern GroupMember *GetGroupMemberData(int group, int member);
extern BOOL IsGroupMemberActive(int group, int member);
extern int Anim_GetFrame(void *anim, int track);
extern int func_0202f4cc(void *anim, int track);

void UpdateObjectEffects(EffectOwner *owner, int step)
{
    EffectContext *context = owner->context;
    TrackState request;
    GroupMember *member;
    int i;

    if (owner->active && !IsGroupMemberActive(owner->groups[0], 0)) {
        owner->active = 0;
    }
    if (owner->active) {
        for (i = 0; i < 2; i++) {
            member = GetGroupMemberData(owner->groups[i], 0);
            if (member->state == 0 && step + Anim_GetFrame(member, 0) >= func_0202f4cc(member, 0)) {
                ResetAnimationTrackState(&request);
                request.id = context->effectId;
                request.loop = 2;
                request.priority = 6;
                request.mode = 1;
                request.target = context->target;
                StopAndClearSoundEmitter(owner->groups[i], 0);
                func_ov021_020a8cc0(&request, owner->groups[i]);
                if (i == 0) {
                    GetGroupMemberData(owner->groups[i], 0)->frame = context->params->frame;
                }
            }
        }
    }
}
