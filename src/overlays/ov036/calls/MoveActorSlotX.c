#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x4];
    s16 width;
    u8 pad_06[0xa];
    fx32 posX;
    u8 pad_14[0x1c];
    fx32 moveFrom;
    fx32 moveTo;
    s32 moveMode;
    s32 moveAxis;
    s32 moveDuration;
    s32 moveTimer;
    u8 pad_48[0x40];
    u16 flags;
    u8 pad_8A[0x12];
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
    u8 pad_0C84[0x40c];
    ActorSlot *slots;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

extern ActorSlotContext data_ov036_020c3940;
extern int FindOrAcquireOwnerSlot(int actorId);

void MoveActorSlotX(int actorId, int startX, int endX, s32 duration)
{
    ActorSlotWork *work = data_ov036_020c3940.work;
    ActorSlot *slot = &work->slots[FindOrAcquireOwnerSlot(actorId)];
    fx32 from = startX << 12;
    fx32 to = endX << 12;

    if (work->skipAnimations != 0) {
        duration = 0;
    }
    switch (startX) {
    case -1000:
        from = (-slot->width >> 1) << 12;
        break;
    case -100:
        from = slot->posX;
        break;
    case 1000:
        from = ((slot->width >> 1) + 0x100) << 12;
        break;
    }
    switch (endX) {
    case -1000:
        to = (-slot->width >> 1) << 12;
        break;
    case 1000:
        to = ((slot->width >> 1) + 0x100) << 12;
        break;
    }
    if (slot->posX == to) {
        return;
    }
    if (duration == 0) {
        slot->posX = to;
        return;
    }
    if (slot->flags & 1) {
        return;
    }
    slot->moveFrom = from;
    slot->posX = from;
    slot->moveTo = to;
    slot->moveDuration = duration;
    slot->moveTimer = duration;
    if (from < 0 || from > 0x100000) {
        slot->moveMode = 5;
    } else if (slot->moveTo < 0 || slot->moveTo > 0x100000) {
        slot->moveMode = 4;
    } else {
        slot->moveMode = 3;
    }
    slot->moveAxis = 0;
    slot->flags |= 1;
}
