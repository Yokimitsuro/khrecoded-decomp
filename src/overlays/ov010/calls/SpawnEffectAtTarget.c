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

typedef struct EventTargetInfo {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct EffectContext {
    u8 pad_000[0x9b4];
    u8 effectId;
} EffectContext;

typedef struct GroupMember {
    u8 pad_00[0xa4];
    VecFx32 position;
} GroupMember;

typedef struct EffectOwner {
    u8 pad_00[0xc];
    void *model;
    u8 pad_10[8];
    int targetId;
    u8 pad_1c[4];
    EffectContext *context;
    u8 pad_24[0x12];
    s16 hitGroup;
} EffectOwner;

extern void ResetAnimationTrackState(TrackState *state);
extern int func_ov021_020a8cc0(TrackState *request, int groupId);
extern void StopAndClearSoundEmitter(int group, int member);
extern GroupMember *GetGroupMemberData(int group, int member);
extern BOOL func_ov001_02087988(u16 id, EventTargetInfo *info);

void SpawnEffectAtTarget(EffectOwner *owner)
{
    EffectContext *context = owner->context;
    TrackState request;
    EventTargetInfo info;
    VecFx32 position;

    if (owner->model != NULL) {
        position = GetGroupMemberData(owner->hitGroup, 0)->position;
        StopAndClearSoundEmitter(owner->hitGroup, 0);
        if (owner->targetId >= 0 && func_ov001_02087988(owner->targetId, &info)) {
            position = info.position;
            position.y += 0x800;
        }
        ResetAnimationTrackState(&request);
        request.id = context->effectId;
        request.loop = 0;
        request.mode = 2;
        request.position = position;
        func_ov021_020a8cc0(&request, owner->hitGroup);
    }
}
