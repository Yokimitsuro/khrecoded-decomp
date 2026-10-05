#include "nitro/types.h"

typedef struct ActorSlot {
    u8 pad_00[0x20];
    s32 depth;
    u8 pad_24[0x6c];
    s32 priority;
    u8 pad_94[0x8];
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0x1090];
    ActorSlot *slots;
    u8 pad_1094[0x40];
    s32 focusMode;
    s32 focusActive;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

extern ActorSlotContext data_ov036_020c3940;
extern int FindOrAcquireOwnerSlot(int actorId);

void SetActorSlotPriority(int actorId, s32 priority)
{
    ActorSlotWork *work = data_ov036_020c3940.work;
    ActorSlot *slot = &work->slots[FindOrAcquireOwnerSlot(actorId)];

    slot->priority = priority;
    if (work->focusMode == 0 && work->focusActive == 0) {
        slot->depth = 0x1000 - (8 - slot->priority) * 0x19a;
    }
}
