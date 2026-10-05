#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[2];
    u16 angle;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 kind;
} MarkerRequest;

typedef struct {
    VecFx32 offset;
    u8 pad_0c[0x1c];
    u16 flags;
    u8 pad_2a[4];
    u16 player;
    u16 variant;
    u8 pad_32[2];
    VecFx32 origin;
    u8 pad_40[8];
} HitEvent;

typedef struct {
    u32 flags;
    VecFx32 hitPos;
    VecFx32 pos;
    u8 pad_1c[4];
    u32 eventId;
    u32 state;
} HitSource;

typedef struct {
    u8 pad_00;
    u8 variant;
} ActorInfo;

typedef struct {
    u8 pad_0000[0x1d4];
    ActorInfo *info;
    u8 pad_01d8[0x9b4 - 0x1d8];
    u8 player;
    u8 pad_09b5[0x1078 - 0x9b5];
    int *reaction;
} Actor;

extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern void MI_CpuFill8(void *dst, int value, int size);
extern int DispatchStageEventArg(u32 id, HitEvent *event);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);

BOOL TryFrontalHitReaction(Actor *actor, HitSource *source)
{
    HitEvent event;
    VecFx32 dir;
    MarkerRequest request;
    int angle;
    BOOL matches;

    if (actor->reaction == NULL) {
        return FALSE;
    }
    if ((source->flags & 8) || (source->flags & 0x20)) {
        return FALSE;
    }
    matches = FALSE;
    if (*actor->reaction == 0x8a) {
        matches = TRUE;
    }
    if (!matches) {
        return FALSE;
    }
    VEC_Subtract(&source->pos, func_ov052_020ceb74(actor), &dir);
    dir.y = 0;
    if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
        int diff;
        VEC_Normalize(&dir, &dir);
        angle = (u16)FX_Atan2Idx(-dir.x, -dir.z);
        diff = (u16)(GetLinkedAngleOffset(actor) - angle);
        if (diff > 0x5000 && diff < 0xb000) {
            return FALSE;
        }
    } else {
        angle = GetLinkedAngleOffset(actor);
    }
    source->state |= 1;
    MI_CpuFill8(&event, 0, sizeof(HitEvent));
    event.player = actor->player;
    event.variant = actor->info->variant;
    event.origin = *func_ov052_020ceb74(actor);
    event.offset.z = 0;
    event.flags |= 4;
    event.offset.y = 0;
    event.offset.x = 0;
    VEC_Subtract(&event.offset, &source->hitPos, &event.offset);
    DispatchStageEventArg((u16)source->eventId, &event);
    ResetAnimationTrackState(&request);
    request.id = actor->player;
    request.unk_25 = 0;
    request.unk_24 = 0;
    request.pos = *func_ov052_020ceb74(actor);
    request.pos.y += 0xf00;
    request.angle = angle + 0x8000;
    request.prevIndex = 0;
    request.kind = 0x1b;
    func_ov021_020a8cc0(&request, func_ov001_0206db8c(0));
    return TRUE;
}
