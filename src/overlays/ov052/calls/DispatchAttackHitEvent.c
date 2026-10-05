#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 offset;
    u8 pad_0c[0x10];
    fx32 knockback;
    u8 pad_20[5];
    u8 element;
    u8 pad_26[2];
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
    u8 pad_10[0x10];
    u32 eventId;
} HitSource;

typedef struct {
    u8 pad_00;
    u8 variant;
} ActorInfo;

typedef struct {
    u8 pad_0000[0x1d4];
    ActorInfo *info;
    u8 pad_01d8[0x9ac - 0x1d8];
    u64 stateFlags;
    u8 player;
} Actor;

extern s16 data_02053580[];
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MI_CpuFill8(void *dst, int value, int size);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int DispatchStageEventArg(u32 id, HitEvent *event);
extern void ApplyScaledHealthDelta(Actor *actor, s32 amount, BOOL force);
extern void AwardPartyGaugePoints(int player, int points);

void DispatchAttackHitEvent(Actor *actor, HitSource *source)
{
    HitEvent event;

    if (!(source->flags & 1)) {
        return;
    }
    MI_CpuFill8(&event, 0, sizeof(HitEvent));
    event.player = actor->player;
    event.variant = actor->info->variant;
    event.origin = *func_ov052_020ceb74(actor);
    event.flags |= 4;
    if (IsPlayerEntryFlagSet(actor->player, 0x3e)) {
        event.element = 1;
    } else if (IsPlayerEntryFlagSet(actor->player, 0x3f)) {
        event.element = 2;
    } else if (IsPlayerEntryFlagSet(actor->player, 0x40)) {
        event.element = 3;
    } else if (IsPlayerEntryFlagSet(actor->player, 0x41)) {
        event.element = 4;
    } else if (IsPlayerEntryFlagSet(actor->player, 0x42)) {
        event.element = 6;
    }
    if (event.element != 0) {
        event.knockback = 0x64000;
    }
    event.offset.z = 0;
    event.offset.y = 0;
    event.offset.x = 0;
    VEC_Subtract(&event.offset, &source->hitPos, &event.offset);
    if (IsPlayerEntryFlagSet(actor->player, 0x4e)) {
        int index = GetLinkedAngleOffset(actor) >> 4;
        event.offset.y = 0;
        event.offset.x = -data_02053580[index];
        event.offset.z = -data_02053580[(0x400 - index) & 0xfff];
        VEC_Normalize(&event.offset, &event.offset);
        func_01ffafb4(0x14cd, &event.offset, &event.offset);
    }
    if (DispatchStageEventArg((u16)source->eventId, &event)) {
        actor->stateFlags |= 4;
    }
    if (IsPlayerEntryFlagSet(actor->player, 0x43)) {
        ApplyScaledHealthDelta(actor, 0x9600, FALSE);
    }
    if (IsPlayerEntryFlagSet(actor->player, 0x1a)) {
        AwardPartyGaugePoints(actor->player, 200);
    }
}
