#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s16 id;
    u8 pad_06[0x26];
} ActorSlot;

typedef struct {
    ActorSlot slots[5];
} ActorSlotGroup;

typedef struct {
    u8 pad_00[0x18];
    s32 id;
    u8 pad_1c[0xc];
} ActorTrack;

typedef struct {
    u8 pad_00[0xc];
    u32 value;
    u8 pad_10[0x14];
} ActorTimer;

typedef struct {
    s32 state;
    u8 pad_004[0xcc];
    ActorSlotGroup groups[6];
    ActorSlot extras[6];
    ActorTrack tracks[7];
    s32 scale;
    s32 target;
    u8 pad_820[0x20];
    s32 counter0;
    s32 counter1;
    s32 counter2;
    s32 counter3;
    s32 counter4;
    s32 counter5;
    s32 counter6;
    u8 pad_85c[0x4c0];
    ActorTimer *timers;
    u8 pad_d20[0x1d4];
    u32 flags;
    u8 pad_ef8[8];
    s32 owner;
    s32 pending;
} ActorObject;

extern void ActorObject_ResetSecondarySlots(ActorObject *actor);
extern void MI_CpuFill8(void *dst, int val, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

void ActorObject_Reset(ActorObject *actor, s32 owner) {
    u32 oldFlags = actor->flags;
    int i;
    int j;

    actor->flags = 0x1d;
    actor->counter5 = 0;
    actor->counter4 = 0;
    actor->counter3 = 0;
    actor->counter2 = 0;
    actor->counter1 = 0;
    actor->counter0 = 0;
    actor->counter6 = 0;
    actor->owner = owner;
    actor->state = 0;
    actor->target = -1;
    actor->scale = 0x1000;
    ActorObject_ResetSecondarySlots(actor);
    actor->pending = 0;
    MI_CpuFill8(actor->tracks, 0, 0x78);
    for (i = 0; i < 7; i++) {
        actor->tracks[i].id = -1;
    }
    MI_CpuFill8(actor->groups, 0, sizeof(actor->groups));
    MI_CpuFill8(actor->extras, 0, sizeof(actor->extras));
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 5; j++) {
            actor->groups[i].slots[j].id = -1;
        }
        actor->extras[i].id = -1;
    }
    if ((oldFlags & 0x2000) == 0) {
        actor->timers = NNSi_FndAllocFromDefaultHeap(0xb4);
        MI_CpuFill8(actor->timers, 0, 0xb4);
        for (i = 0; i < 5; i++) {
            actor->timers[i].value = 0;
        }
    }
}
